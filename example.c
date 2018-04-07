
static void nus_data_handler(ble_nus_evt_t * p_evt)
{

    if (p_evt->type == BLE_NUS_EVT_RX_DATA)
    {
        uint32_t err_code;

        NRF_LOG_DEBUG("Received data from BLE NUS. Writing data on UART.");
        NRF_LOG_HEXDUMP_DEBUG(p_evt->params.rx_data.p_data, p_evt->params.rx_data.length);

		//Let's say you have a button called "TEST" - if clicked, then the code inside the else will fire
        if (strncmp(p_evt->params.rx_data.p_data,"TEST",strlen(p_evt->params.rx_data.p_data))) {}
        else {
            NRF_LOG_DEBUG("Walky Talky is working");
        }
        //These are how you toggle the LEDs.
        //For this to work, paste this inside the main function at the bottom of your code:
        /*
			//Set LEDs to be outputs
			//Note - LEDs are reversed, so set will clear them and clear will set them
    		nrf_gpio_cfg_output(LED_1);
    		nrf_gpio_cfg_output(LED_2);
    		nrf_gpio_cfg_output(LED_3);
    		nrf_gpio_cfg_output(LED_4);
        */
        if (strncmp(p_evt->params.rx_data.p_data,"CMNDA",strlen(p_evt->params.rx_data.p_data))) {}
        else {
            NRF_LOG_DEBUG("LED_1 Activate");
            nrf_gpio_pin_toggle(LED_1);
        }
        if (strncmp(p_evt->params.rx_data.p_data,"CMNDB",strlen(p_evt->params.rx_data.p_data))) {}
        else {
            NRF_LOG_DEBUG("LED_2 Activate");
            nrf_gpio_pin_toggle(LED_2);
        }
        if (strncmp(p_evt->params.rx_data.p_data,"CMNDC",strlen(p_evt->params.rx_data.p_data))) {}
        else {
            NRF_LOG_DEBUG("LED_3 Activate");
            nrf_gpio_pin_toggle(LED_3);
        }
        if (strncmp(p_evt->params.rx_data.p_data,"CMNDD",strlen(p_evt->params.rx_data.p_data))) {}
        else {
            NRF_LOG_DEBUG("LED_4 Activate");
            nrf_gpio_pin_toggle(LED_4);
        }
		
        //We can also talk to specific pins.  Let's say we want to send a signal from pin "PO.27"
        //First, paste this to main:
        /*
		 	nrf_gpio_cfg_output(27);
        */
        //Then we can toggle it with nrf_gpio_pin_toggle(27), turn it on with nrf_gpio_pin_set(27), and
        //turn it off with nrf_gpio_pin_clear(27)  Obviously we can replace '27' with any of the pins
		
        //If we want to recieve output, paste this to main:
        /*
		 	nrf_gpio_cfg_input(27);
        */
        //And the input is returned by nrf_gpio_pin_read(27);


        for (uint32_t i = 0; i < p_evt->params.rx_data.length; i++)
        {
            do
            {
                err_code = app_uart_put(p_evt->params.rx_data.p_data[i]);
                if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_BUSY))
                {
                    NRF_LOG_ERROR("Failed receiving NUS message. Error 0x%x. ", err_code);
                    APP_ERROR_CHECK(err_code);
                }
            } while (err_code == NRF_ERROR_BUSY);
        }
        if (p_evt->params.rx_data.p_data[p_evt->params.rx_data.length - 1] == '\r')
        {
            while (app_uart_put('\n') == NRF_ERROR_BUSY);
        }
    }

}
