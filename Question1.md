I have clock/thermometer/hygrometer combo that has a remote sender unit and together they have the following features:
On an LCD, the main unit:
1. shows current time
2. shows the phase of the Moon
3. shows time of sunrise for selected US cities
4. shows time of sunset for selected US cities
5. shows the temperature and humidity sensed by the main unit 
6. shows the temperature and humidity sensed by the remote unit(s)

The remote unit should have a very minimal microcontroller, a temperature and a humidity sensor, and a very low power 
RF transmitter. While I haven't verified how it works [by measuring current draw over a period of time], the microcontroller
probably sleeps most of the time, wakes up periodically  (i.e. once a minute), reads the sensors transmits the data, and 
then goes back to sleep.

The main unit is somewhat more complicated -- it should have an RF receiver that's probably on all the time (as per spec 
sheet, it supports up to four remote units), some driver code for the LCD, and some code to compute sunset/sunrise/Moon 
phase based on longitude and latitude.

With respect to embedded systems programming, for the most parts, I consider this a very straightforward system -- something 
that's relatively easy to design and implement.

I think the most challenging part could be to come with the algorithm to correctly compute sunset, sunrise, and 
the Moon phase for selectable cities, and fit all that into a likely to be very limited code space. That could be 
either mostly computational, or computation aided with a pre-computed look-up-table. 
