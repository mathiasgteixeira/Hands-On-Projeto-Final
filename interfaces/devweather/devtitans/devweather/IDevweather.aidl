package devtitans.devweather;

@VintfStability
interface IDevweather {
        int connect();
        String getAll();
	float getHumidity();
	float getTemperatureDHT();
	float getLux();
	float getTemperatureBMP();
	float getPressure();
	float getAltitude();
	float getAverageTemperature();
	float getHeatIndex();

}
