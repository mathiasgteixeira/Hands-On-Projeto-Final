#include <linux/module.h>
#include <linux/usb.h>
#include <linux/slab.h>

MODULE_AUTHOR("DevTITANS <devtitans@icomp.ufam.edu.br>");
MODULE_DESCRIPTION("Driver de acesso ao DevWeather (ESP32 com Chip Serial CP2102)");
MODULE_LICENSE("GPL");

#define MAX_RECV_LINE 100

static int  usb_probe(struct usb_interface *ifce, const struct usb_device_id *id); 
static void usb_disconnect(struct usb_interface *ifce);
static int  usb_send_cmd(char *cmd, int param, char *response);                                     
static ssize_t attr_show(struct kobject *sys_obj, struct kobj_attribute *attr, char *buff);
static ssize_t attr_store(struct kobject *sys_obj, struct kobj_attribute *attr, const char *buff, size_t count);

static char recv_line[MAX_RECV_LINE];
static struct usb_device *devweather_device;
static uint usb_in, usb_out;
static char *usb_in_buffer, *usb_out_buffer;
static int usb_max_size;

static struct kobj_attribute allc_attribute = __ATTR(allc, S_IRUGO, attr_show, attr_store);

static struct attribute *attrs[] = { 
    &allc_attribute.attr, 
    NULL 
};

static struct attribute_group attr_group = { .attrs = attrs };
static struct kobject *sys_obj;

#define VENDOR_ID  0x10C4  
#define PRODUCT_ID 0xEA60  
static const struct usb_device_id id_table[] = { { USB_DEVICE(VENDOR_ID, PRODUCT_ID) }, {} };
MODULE_DEVICE_TABLE(usb, id_table);
bool ignore = true;

static struct usb_driver devweather_driver = {
    .name        = "devweather",
    .probe       = usb_probe,
    .disconnect  = usb_disconnect,
    .id_table    = id_table,
};
module_usb_driver(devweather_driver);

static int usb_probe(struct usb_interface *interface, const struct usb_device_id *id) {
    struct usb_endpoint_descriptor *usb_endpoint_in, *usb_endpoint_out;

    printk(KERN_INFO "DevWeather: Dispositivo conectado ...\n");

    sys_obj = kobject_create_and_add("devweather", kernel_kobj);
    ignore = sysfs_create_group(sys_obj, &attr_group);

    devweather_device = interface_to_usbdev(interface);
    ignore = usb_find_common_endpoints(interface->cur_altsetting, &usb_endpoint_in, &usb_endpoint_out, NULL, NULL);
    usb_max_size = usb_endpoint_maxp(usb_endpoint_in);
    usb_in = usb_endpoint_in->bEndpointAddress;
    usb_out = usb_endpoint_out->bEndpointAddress;
    usb_in_buffer = kmalloc(usb_max_size, GFP_KERNEL);
    usb_out_buffer = kmalloc(usb_max_size, GFP_KERNEL);

    return 0;
}

static void usb_disconnect(struct usb_interface *interface) {
    printk(KERN_INFO "DevWeather: Dispositivo desconectado.\n");
    if (sys_obj) kobject_put(sys_obj);
    kfree(usb_in_buffer);
    kfree(usb_out_buffer);
}

static int usb_send_cmd(char *cmd, int param, char *response) {
    int recv_size = 0;
    int ret, actual_size, i;
    int retries = 10;
    char resp_expected[MAX_RECV_LINE];

    printk(KERN_INFO "DevWeather: Enviando comando: %s\n", cmd);

    // Verifica se o comando tem um parâmetro ou não
    if (param >= 0) 
        sprintf(usb_out_buffer, "%s %d\n", cmd, param);  // Inclui o parâmetro se ele for >= 0
    else 
        sprintf(usb_out_buffer, "%s\n", cmd);            // Apenas o comando, sem parâmetro

    // Envia o comando via USB
    ret = usb_bulk_msg(devweather_device, usb_sndbulkpipe(devweather_device, usb_out), usb_out_buffer, strlen(usb_out_buffer), &actual_size, 1000*HZ);
    if (ret) {
        printk(KERN_ERR "DevWeather: Erro ao enviar comando!\n");
        return -1;
    }

    sprintf(resp_expected, "RES %s", cmd);  // Resposta esperada

    while (retries > 0) {
        ret = usb_bulk_msg(devweather_device, usb_rcvbulkpipe(devweather_device, usb_in), usb_in_buffer, min(usb_max_size, MAX_RECV_LINE), &actual_size, HZ*1000);
        if (ret) {
            printk(KERN_ERR "DevWeather: Erro ao ler dados da USB. Tentativas restantes: %d\n", retries--);
            continue;
        }

        for (i = 0; i < actual_size; i++) {
            if (usb_in_buffer[i] == '\n') {
                recv_line[recv_size] = '\0';
                printk(KERN_INFO "DevWeather: Linha recebida: '%s'\n", recv_line);

                // Copia a resposta recebida para o buffer passado como parâmetro
                strcpy(response, recv_line);
                return 0;  // Sucesso
            } else {
                recv_line[recv_size] = usb_in_buffer[i];
                recv_size++;
            }
        }
    }

    return -1;  // Se chegou aqui, houve um erro
}

static ssize_t attr_show(struct kobject *sys_obj, struct kobj_attribute *attr, char *buff) {
    char response[MAX_RECV_LINE] = {0};
    const char *attr_name = attr->attr.name;

    printk(KERN_INFO "DevWeather: Lendo %s ...\n", attr_name);

    if (!strcmp(attr_name, "allc")) {
        if (usb_send_cmd("GET_ALLC", -1, response) == 0) {
            // Copia a resposta completa para o buffer de saída
            sprintf(buff, "%s\n", response);
        } else {
            sprintf(buff, "Erro ao comunicar com o dispositivo\n");
        }
    } else {
        sprintf(buff, "Atributo %s desconhecido\n", attr_name);
    }

    return strlen(buff);
}

static ssize_t attr_store(struct kobject *sys_obj, struct kobj_attribute *attr, const char *buff, size_t count) {
    return -EACCES; // Nenhum dos atributos do DevWeather pode ser escrito (somente leitura)
}
