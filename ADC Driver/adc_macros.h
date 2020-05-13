//Macros file for adc.c

//Channel read-enable bits - set to 0 to disable specific channels, set to 1 to enable
//No other code changes need to be made to enable/disable channels
#define CH0_EN                (1)
#define CH1_EN                (1)
#define CH2_EN                (1)
#define CH3_EN                (1)
#define CH4_EN                (1)
#define CH5_EN                (0)
#define CH6_EN                (0)
#define CH7_EN                (0)
//Filenames for channel data - change output filenames here
#define CH0_FILENAME          "tempSensorCommon.txt"
#define CH1_FILENAME          "ductTemp.txt"
#define CH2_FILENAME          "ambientTemp.txt"
#define CH3_FILENAME          "ductHumidity.txt"
#define CH4_FILENAME          "ambientHumidity.txt"
#define CH5_FILENAME          "channel_5.txt"
#define CH6_FILENAME          "channel_6.txt"
#define CH7_FILENAME          "channel_7.txt"
//Other configurable stuff:
#define READ_INTERVAL         (1000) //time between ADC readings in milliseconds
#define CS_PIN                (21) //GPIO connected to chip select of the MCP3008 (use WiringPi GPIO #s)
#define VOLTAGE_CONVERSION    (0.00390625) //Specific to 3.5V reference (divide ref. voltage by 1024)
#define WRITE_TYPE            "w" //"w" to overwrite old data, "a" to append
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Thermistor stuff:
#define B_COEFF (3950)
#define TEMP_NOMINAL (298.15)
#define RESISTANCE_NOMINAL (100000)
#define R_INF (0.176323) //R_INF = RESISTANCE_NOMINAL*exp(-B_COEFF/TEMP_NOMINAL)
#define RESISTANCE_FIXED (100000) //this is the value of the other resistor that makes up the resistive divider
//Misc:
#define ALWAYS            (1)
#define L_SHIFT_EIGHT		  (8)
// SPI stuff:
#define SPI_CLK 			    (500000)
#define SPI_CHNL			    (0)
#define BUFFER_SIZE			  (5)
#define BUFFER_LENGTH		  (3)
//Buffer values for all channel reads:
#define BUF_ZERO			    (0x01)
#define BUF_TWO				    (0x00)
//Buffer values for specific channel reads:
#define CH0_BUF_ONE				(0x80)
#define CH1_BUF_ONE				(0x90)
#define CH2_BUF_ONE				(0xA0)
#define CH3_BUF_ONE				(0xB0)
#define CH4_BUF_ONE				(0xC0)
#define CH5_BUF_ONE				(0xD0)
#define CH6_BUF_ONE				(0xE0)
#define CH7_BUF_ONE				(0xF0)
//Channel-identifying macros:
#define CH0               (0)
#define CH1               (1)
#define CH2               (2)
#define CH3               (3)
#define CH4               (4)
#define CH5               (5)
#define CH6               (6)
#define CH7               (7)
