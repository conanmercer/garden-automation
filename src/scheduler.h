class Scheduler
{
private:
    unsigned long lastIrrigationRun = 0;
    unsigned long irrigationInterval;

public:
    Scheduler(unsigned long irrigationInterval) : irrigationInterval(irrigationInterval) {}

    void run(unsigned long currentTime)
    {
        if (currentTime - lastIrrigationRun >= irrigationInterval)
        {
            runIrrigation();
            Serial.println("Irrigation completed.");
            lastIrrigationRun = currentTime;
        }
    }

    void setIrrigationInterval(unsigned long interval)
    {
        irrigationInterval = interval;
    }

    void setLastIrrigationRun(unsigned long time)
    {
        lastIrrigationRun = time;
    }
};
