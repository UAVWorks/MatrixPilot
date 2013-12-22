// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


#include "libUDB_internal.h"

#if (BOARD_TYPE == UDB4_BOARD)

	//	Measure the pulse widths of the servo channel inputs from the radio.
	//	The dsPIC makes this rather easy to do using its capture feature.
	
	//	One of the channels is also used to validate pulse widths to detect loss of radio.
	
	//	The pulse width inputs can be directly converted to units of pulse width outputs to control
	//	the servos by simply dividing by 2.
	
	int udb_pwIn[NUM_INPUTS+1] ;	// pulse widths of radio inputs
	int udb_pwTrim[NUM_INPUTS+1] ;	// initial pulse widths for trimming
	
	//   ////////  sonar support   ////////
	#if ( USE_SONAR	== 1 )
		int udb_pwm_sonar  ;		// pulse width of sonar signal sent to altitudeCntrl.c
		int udb_pwm_sonar_rise ;
	#endif
	
	int failSafePulses = 0 ;
	int noisePulses = 0 ;
	
	
	#if (USE_PPM_INPUT != 1)
		unsigned int rise[NUM_INPUTS+1] ;	// rising edge clock capture for radio inputs
	#else
		#define MIN_SYNC_PULSE_WIDTH 7000	// 3.5ms
		unsigned int rise_ppm ;				// rising edge clock capture for PPM radio input
	#endif
	
	
	void udb_init_capture(void)
	{
	int i; 
	
	#if(USE_NV_MEMORY == 1)
		if(udb_skip_flags.skip_radio_trim == 0)
		{	
	#endif
		for (i=0; i <= NUM_INPUTS; i++)
		#if (FIXED_TRIMPOINT == 1)
			if(i == THROTTLE_OUTPUT_CHANNEL)
				udb_pwTrim[i] = udb_pwIn[i] = THROTTLE_TRIMPOINT;
			else
				udb_pwTrim[i] = udb_pwIn[i] = CHANNEL_TRIMPOINT;			
		#else
			udb_pwTrim[i] = udb_pwIn[i] = 0 ;
		#endif
	#if(USE_NV_MEMORY == 1)
		}
	#endif
		
		TMR2 = 0 ; 				// initialize timer
		T2CONbits.TCKPS = 1 ;	// prescaler = 8 option
		T2CONbits.TCS = 0 ;		// use the internal clock
		T2CONbits.TON = 1 ;		// turn on timer 2
		
		//	configure the capture pins
		IC1CONbits.ICTMR = 1 ;  // use timer 2
		IC1CONbits.ICM = 1 ; // capture every edge
		_TRISD8 = 1 ;
		_IC1IP = 6 ;
		_IC1IF = 0 ;
	
	//   ////////  sonar support   ////////
	#if ( USE_SONAR	== 1 )
		// Setup Channel 8 for Sonar
	    // Sonar PWM Pulses are at 58 micro seconds per cm measured. Maximum is 765 cm. So Max Pulse is 44370 micro seconds.
	    // Clock of timer is running at 16,000,000 Hz. So Max Sonar Pulse is 16000000 * 0.044379 clock pulses whih is 710064 pulses. 
	    // If prescales of the timer is set to 64, then maxumum sonar measurement within matrixPIlot is 710064 / 64 = 11095.
	    // If minimum reading is 0.2 meters, then minimum PWM is  (20 * 58) = 1160 micro seconds. So the
	    // minimum integer in MatrixPilot should then be (16000000 * 0.001160) / 64 = 290
		// Each unit of UDB PWM sonar pulse is 64 / 16000000 seconds which is 0.000004 seconds in length.
	    // Therefore each centimeter of measured distance will show 0.000058 / 0.000004 or 58 or 14.5 UDB PWM sonar units / centimeter.
	
		TMR3 = 0 ; 				// initialize timer
		T3CONbits.TCKPS = 2 ;	// prescaler = 64,  see page 175 at http://ww1.microchip.com/downloads/en/DeviceDoc/70593C.pdf
		T3CONbits.TCS = 0 ;		// use the internal clock
		T3CONbits.TON = 1 ;		// turn on timer 3
	
	    IC8CONbits.ICTMR = 0 ;  // use timer 3
		IC8CONbits.ICM = 1 ; // capture every edge
		_TRISD15 = 1 ;
		_IC8IP = 6 ;
		_IC8IF = 0 ; 
	#endif
	//   ////////  sonar support mod end  ////////    
		if (NUM_INPUTS > 0) _IC1IE = 1 ;
		
	#if (USE_PPM_INPUT != 1)
		IC7CON  = IC6CON   = IC5CON   = IC4CON   = IC3CON   = IC2CON   = IC1CON ; //  sonar support mod
		_TRISD9 = _TRISD10 = _TRISD11 = _TRISD12 = _TRISD13 = _TRISD14 = _TRISD8 ; //  sonar support mod
		//  sonar support add
		#if ( USE_SONAR	!= 1 )
			 _TRISD15 = _TRISD8 ;
		#endif
			
		//	set the interrupt priorities to 6
		_IC2IP = _IC3IP = _IC4IP = _IC5IP = _IC6IP = _IC7IP  = _IC1IP ; //  sonar support mod
		//  sonar support add
		#if ( USE_SONAR	!= 1 )
			 _IC8IP = _IC1IP ;
		#endif 
		
		//	clear the interrupts:
		_IC2IF = _IC3IF = _IC4IF = _IC5IF = _IC6IF = _IC7IF = _IC8IF = _IC1IF ;
		
		//	enable the interrupts:
		if (NUM_INPUTS > 1) _IC2IE = 1 ; 
		if (NUM_INPUTS > 2) _IC3IE = 1 ; 
		if (NUM_INPUTS > 3) _IC4IE = 1 ; 
		if (NUM_INPUTS > 4) _IC5IE = 1 ; 
		if (NUM_INPUTS > 5) _IC6IE = 1 ; 
		if (NUM_INPUTS > 6) _IC7IE = 1 ; 
		if ((NUM_INPUTS > 7) || ( USE_SONAR == 1)) _IC8IE = 1 ; //  sonar support mod
	#else   //#IF (USE_PPM_INPUT ==1)
		if (USE_SONAR == 1) _IC8IE = 1 ; // enable sonar intterupt
	#endif  //#IF (USE_PPM_INPUT !=1)
		
	return ;
	}
	
	#if (USE_PPM_INPUT != 1)
		
		// Input Channel 1
		void __attribute__((__interrupt__,__no_auto_psv__)) _IC1Interrupt(void)
		{
			indicate_loading_inter ;
			interrupt_save_set_corcon ;
			
			unsigned int time ;	
			_IC1IF = 0 ; // clear the interrupt
			while ( IC1CONbits.ICBNE )
			{
				time = IC1BUF ;
			}
			
		#if ( NORADIO != 1 )
			if (PORTDbits.RD8)
			{
				 rise[1] = time ;
			}
			else
			{
				udb_pwIn[1] = time - rise[1] ;
				
		#if ( FAILSAFE_INPUT_CHANNEL == 1 )
				if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
				{
					failSafePulses++ ;
				}
				else
				{
					noisePulses++ ;
				}
		#endif
			
			}
		#endif
			
			interrupt_restore_corcon ;
			return ;
		}
		
		// Input Channel 2
		void __attribute__((__interrupt__,__no_auto_psv__)) _IC2Interrupt(void)
		{
			indicate_loading_inter ;
			interrupt_save_set_corcon ;
			
			unsigned int time ;
			_IC2IF = 0 ; // clear the interrupt
			while ( IC2CONbits.ICBNE )
			{
				time = IC2BUF ;
			}
			
		#if ( NORADIO != 1 )
			if (PORTDbits.RD9)
			{
				 rise[2] = time ;
			}
			else
			{
				udb_pwIn[2] = time - rise[2] ;
				
		#if ( FAILSAFE_INPUT_CHANNEL == 2 )
				if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
				{
					failSafePulses++ ;
				}
				else
				{
					noisePulses++ ;
				}
		#endif
			
			}	
		#endif
			
			interrupt_restore_corcon ;
			return ;
		}
		
		// Input Channel 3
		void __attribute__((__interrupt__,__no_auto_psv__)) _IC3Interrupt(void)
		{
			indicate_loading_inter ;
			interrupt_save_set_corcon ;
			
			unsigned int time ;
			_IC3IF = 0 ; // clear the interrupt
			while ( IC3CONbits.ICBNE )
			{
				time = IC3BUF ;
			}
			
		#if ( NORADIO != 1 )
			if (PORTDbits.RD10)
			{
				 rise[3] = time ;
			}
			else
			{
				udb_pwIn[3] = time - rise[3] ;
				
		#if ( FAILSAFE_INPUT_CHANNEL == 3 )
				if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
				{
					failSafePulses++ ;
				}
				else
				{
					noisePulses++ ;
				}
		#endif
			
			}
		#endif
			
			interrupt_restore_corcon ;
			return ;
		}
		
		// Input Channel 4
		void __attribute__((__interrupt__,__no_auto_psv__)) _IC4Interrupt(void)
		{
			indicate_loading_inter ;
			interrupt_save_set_corcon ;
			
			unsigned int time ;
			_IC4IF =  0 ; // clear the interrupt
			while ( IC4CONbits.ICBNE )
			{
				time = IC4BUF ;
			}
			
		#if ( NORADIO != 1 )
			if (PORTDbits.RD11)
			{
				 rise[4] = time ;
			}
			else
			{
				udb_pwIn[4] = time - rise[4] ;
				
		#if ( FAILSAFE_INPUT_CHANNEL == 4 )
				if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
				{
					failSafePulses++ ;
				}
				else
				{
					noisePulses++ ;
				}
		#endif
			
			}
		#endif
			
			interrupt_restore_corcon ;
			return ;
		}
		
		// Input Channel 5
		void __attribute__((__interrupt__,__no_auto_psv__)) _IC5Interrupt(void)
		{
			indicate_loading_inter ;
			interrupt_save_set_corcon ;
			
			unsigned int time ;
			_IC5IF =  0 ; // clear the interrupt
			while ( IC5CONbits.ICBNE )
			{
				time = IC5BUF ;
			}
			
		#if ( NORADIO != 1 )
			if (PORTDbits.RD12)
			{
				 rise[5] = time ;
			}
			else
			{
				udb_pwIn[5] = time - rise[5] ;
				
		#if ( FAILSAFE_INPUT_CHANNEL == 5 )
				if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
				{
					failSafePulses++ ;
				}
				else
				{
					noisePulses++ ;
				}
		#endif
			
			}
		#endif
			
			interrupt_restore_corcon ;
			return ;
		}
		
		// Input Channel 6
		void __attribute__((__interrupt__,__no_auto_psv__)) _IC6Interrupt(void)
		{
			indicate_loading_inter ;
			interrupt_save_set_corcon ;
			
			unsigned int time ;
			_IC6IF =  0 ; // clear the interrupt
			while ( IC6CONbits.ICBNE )
			{
				time = IC6BUF ;
			}
			
		#if ( NORADIO != 1 )
			if (PORTDbits.RD13)
			{
				 rise[6] = time ;
			}
			else
			{
				udb_pwIn[6] = time - rise[6] ;
				
		#if ( FAILSAFE_INPUT_CHANNEL == 6 )
				if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
				{
					failSafePulses++ ;
				}
				else
				{
					noisePulses++ ;
				}
		#endif
			
			}
		#endif
			
			interrupt_restore_corcon ;
			return ;
		}
		
		// Input Channel 7
		void __attribute__((__interrupt__,__no_auto_psv__)) _IC7Interrupt(void)
		{
			indicate_loading_inter ;
			interrupt_save_set_corcon ;
			
			unsigned int time ;
			_IC7IF =  0 ; // clear the interrupt
			while ( IC7CONbits.ICBNE )
			{
				time = IC7BUF ;
			}
			
		#if ( NORADIO != 1 )
			if (PORTDbits.RD14)
			{
				 rise[7] = time ;
			}
			else
			{
				udb_pwIn[7] = time - rise[7] ;
				
		#if ( FAILSAFE_INPUT_CHANNEL == 7 )
				if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
				{
					failSafePulses++ ;
				}
				else
				{
					noisePulses++ ;
				}
		#endif
			
			}
		#endif
			
			interrupt_restore_corcon ;
			return ;
		}
		  
	// Input Channel 8
	#if ( USE_SONAR	!= 1 )
	void __attribute__((__interrupt__,__no_auto_psv__)) _IC8Interrupt(void)
	{
		indicate_loading_inter ;
		interrupt_save_set_corcon ;
		
		unsigned int time ;
		_IC8IF =  0 ; // clear the interrupt
		while ( IC8CONbits.ICBNE )
		{
			time = IC8BUF ;
		}
		
		#if ( NORADIO != 1 )
			if (PORTDbits.RD15)
			{
				 rise[8] = time ;
			}
			else
			{
				udb_pwIn[8] = time - rise[8] ;
				
		#if ( FAILSAFE_INPUT_CHANNEL == 8 )
				if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
				{
					failSafePulses++ ;
				}
				else
				{
					noisePulses++ ;
				}
		#endif	
			}
		#endif
		
		interrupt_restore_corcon ;
		return ;
	}
	#endif
		//  ///////// sonar support add end  /////////
		
	#else // ///////     #if (USE_PPM_INPUT == 1)
	
		#if (PPM_SIGNAL_INVERTED == 1)
			#define PPM_PULSE_VALUE 0
		#else
			#define PPM_PULSE_VALUE 1
		#endif
		
		unsigned char ppm_ch = 0 ;
		
		// PPM Input on Channel 1
		void __attribute__((__interrupt__,__no_auto_psv__)) _IC1Interrupt(void)
		{
			indicate_loading_inter ;
			interrupt_save_set_corcon ;
			
			unsigned int time ;	
			_IC1IF = 0 ; // clear the interrupt
			while ( IC1CONbits.ICBNE )
			{
				time = IC1BUF ;
			}
			
		#if ( NORADIO != 1 )
		
			if (_RD8 == PPM_PULSE_VALUE)
			{
				unsigned int pulse = time - rise_ppm ;
				rise_ppm = time ;
				
				if (pulse > MIN_SYNC_PULSE_WIDTH)			//sync pulse
				{
					ppm_ch = 1 ;
				}
				else
				{
					if (ppm_ch > 0 && ppm_ch <= PPM_NUMBER_OF_CHANNELS)
					{
						if (ppm_ch <= NUM_INPUTS)
						{
							udb_pwIn[ppm_ch] = pulse ;
							
							if ( ppm_ch == FAILSAFE_INPUT_CHANNEL )
							{
								if ( udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN && udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX )
								{
									failSafePulses++ ;
								}
								else
								{
									noisePulses++ ;
								}
							}
						}
						ppm_ch++ ;							//scan next channel
					}
				}
			}
		#endif
			interrupt_restore_corcon ;
			return ;
		}
		
	#endif // #if (USE_PPM_INPUT != 1)

	#if (USE_SONAR	== 1)
	unsigned int sonar_pwm_count ;
	void __attribute__((__interrupt__,__no_auto_psv__)) _IC8Interrupt(void)
	{
		indicate_loading_inter ;
		interrupt_save_set_corcon ;
		
		unsigned int time ;
		_IC8IF =  0 ; // clear the interrupt
		while ( IC8CONbits.ICBNE )
		{
			time = IC8BUF ;
		}
		if (PORTDbits.RD15)
		{
			udb_pwm_sonar_rise = time ;
			sonar_pwm_count++ ;
		}
		else
		{
			udb_pwm_sonar = time - udb_pwm_sonar_rise ;	
			udb_flags._.sonar_updated = 1;
		}	
		interrupt_restore_corcon ;
		return ;
	}
		
	#endif // ( USE_SONAR_ON_PWM_INPUT_8	is True )

#endif // #if (BOARD_TYPE == UDB4_BOARD)
