    # define red1 portd.B0
    # define yellow1 portd.B1
    # define green1 portd.B2
    # define red2 portd.B3
    # define yellow2 portd.B4
    # define green2 portd.B5

    #define msd1 porta.B0
    #define lsd1 porta.B1
    #define msd2 porta.B2
    #define lsd2 porta.B3

    #define switch porta.B5
    #define manual portb.B0

    void interrupt() // Interrupt block of code.
    {
        if(INTE_bit==1) // If manual button is clicked, then
        {
            lsd1=msd1=0;// All 7-segs
            lsd2=msd2=0;// are off
            if(red2==1&&yellow1==0&&green1==0){green1=1;} // Manual button may be
            if(red1==1&&yellow2==0&&green2==0){green2=1;} // clicked during flashing.
            while(1)
            {
                while(switch==1); // Waiting switch button to be clicked.
                    if(red1==1) // If west street red light is on, then
                    {
                        if(yellow2==0)
                        {
                            yellow2=1; // south street yellow light will be on
                            green2=0; // and green light will be off.
                        }
                        delay_ms(3000); //After 3 secs, then
                        red1=0; // west street red light will be off
                        green1=1; // ,west street green light will be on
                        red2=1; // ,south street red light will be on
                        yellow2=0; // and south street yellow light will be off.
                        while(switch==1); // Waiting switch button to be clicked.
                    }
                    if(red2==1)
                    {
                        if(yellow2==0)
                        {
                            yellow1=1;
                            green1=0;
                        }
                        delay_ms(3000);
                        red2=0;
                        green2=1;
                        red1=1;
                        yellow1=0;
                    }
                    while(switch==0); // Waiting switch button to be clicked.
            }
        }
    }
    
    signed char A;
    signed char B;
    signed char i;
    void main()
    {
        while(porta.b4==0); //Start button.
        adcon1=7; //Converting PORTA from analog to digital.
        trisa=trisc=trisd=0; //Setting PORTA, PORTC and PORTD as output
        trisa.B5=1; //Setting RA5 (switch button) as input.
        trisb.B0=1; //Setting RB0 (manual button) as input.
        GIE_bit=1; //Setting general interrupt enalbe to on state.
        INTE_bit=1; //Setting RB0 (manual button) interrupt enalbe to on state.
        NOT_RBPU_bit=0; //Enable internal Vdd and pull-up resistance.
        INTEDG_bit=0; //Falling egde.
        while(1) //Endless loop.
        {
            red1=1; //Red light of west street is on.
            yellow1=0;
            green1=0;
            red2=0;
            yellow2=0;
            green2=1; //Green light of south street is on.
            for (A=15;A>=0;A--) //15 seconds counting down.
            {
                i=A-3;
                if(A<=3)
                    {
                        i=A;
                        yellow2=1; //Yellow light of south street is on.
                        green2=0; //Green light of south street is off.
                    }
                for(B=0;B<25;B++) //Desplaying numbers for one second (25*40=1000ms=1s).
                {
                    if(A<=6&&A>3&&B==6 ){green2=~green2;} //(Additional) Green light flashing at last 3 seconds of its time.
                    if(A<=6&&A>3&&B==12){green2=~green2;}
                    if(A<=6&&A>3&&B==18){green2=~green2;}
                    lsd1=1; // Right 7-seg of west street is on.
                    msd1=0;
                    lsd2=0;
                    msd2=0;
                    portc=A%10;
                    delay_ms(10);
                    lsd1=0;
                    msd1=1; // Left 7-seg of west street is on.
                    lsd2=0;
                    msd2=0;
                    portc=A/10;
                    delay_ms(10);
                    lsd1=0;
                    msd1=0;
                    lsd2=1; // Right 7-seg of south street is on.
                    msd2=0;
                    portc=i%10;
                    delay_ms(10);
                    lsd1=0;
                    msd1=0;
                    lsd2=0;
                    msd2=1; // Left 7-seg of south street is on.
                    portc=i/10;
                    delay_ms(10);
                }
                if(A<=6&&A>3){green2=~green2;} //(Additional) Green light flashing at last 3 seconds of its time.
            }
            red1=0; //Red light of west street is off.
            green1=1; //Green light of west street is on.
            red2=1; //Red light of south street is on.
            yellow2=0; //Yellow light of south street is off.
            for (A=23;A>=0;A--) //23 seconds counting down.
            {
                i=A-3;
                if(A<=3)
                {
                    i=A;
                    yellow1=1;
                    green1=0;
                }
                for(B=0;B<25;B++)
                {
                    if(A<=6&&A>3&&B==6 ){green1=~green1;}
                    if(A<=6&&A>3&&B==12){green1=~green1;}
                    if(A<=6&&A>3&&B==18){green1=~green1;}
                    lsd1=1;
                    msd1=0;
                    lsd2=0;
                    msd2=0;
                    portc=i%10;
                    delay_ms(10);
                    lsd1=0;
                    msd1=1;
                    lsd2=0;
                    msd2=0;
                    portc=i/10;
                    delay_ms(10);
                    lsd1=0;
                    msd1=0;
                    lsd2=1;
                    msd2=0;
                    portc=A%10;
                    delay_ms(10);
                    lsd1=0;
                    msd1=0;
                    lsd2=0;
                    msd2=1;
                    portc=A/10;
                    delay_ms(10);
                }
                    if(A<=6&&A>3){green1=~green1;}
            }
        }
    }