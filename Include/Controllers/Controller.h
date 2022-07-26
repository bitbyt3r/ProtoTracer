#pragma once
#include "../Utils/utils.h"
#include "../Render/Camera.h"

long mapValue(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

class Controller {
private:
    const float softStart = 3000000;//microseconds
    long previousTime;
    Camera** cameras;
    uint8_t count = 0;
    float renderTime = 0.0f;
    uint8_t maxBrightness;
    bool isOn = false;

protected:
    uint8_t brightness;

    Controller(Camera** cameras, uint8_t count, uint8_t maxBrightness){
        this->cameras = cameras;
        this->count = count;
        this->maxBrightness = maxBrightness;
	    previousTime = micros();
    }

public:
    void Render(Scene* scene){
	    previousTime = micros();

        if (!isOn && previousTime < softStart){
	        brightness = mapValue(previousTime, 0, softStart, 0, maxBrightness);
        }
        else if (!isOn){
            brightness = maxBrightness;
            isOn = true;
        }
#pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < count; i++){
            cameras[i]->Rasterize(scene);
        }

	    renderTime = ((float)(micros() - previousTime)) / 1000000.0f;
    }

    virtual void Initialize() = 0;
    virtual void Display() = 0;

    float GetRenderTime(){
        return renderTime;
    }

};
