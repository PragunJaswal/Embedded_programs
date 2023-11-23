#include <EloquentTinyML.h>
// c_model_posture.h contains the array you exported from the previous step with xxd or tinymlgen
#include "c_model_posture.h"

#define NUMBER_OF_INPUTS 3
#define NUMBER_OF_OUTPUTS 2
// in future projects you may need to tweek this value: it's a trial and error process
#define TENSOR_ARENA_SIZE 2*1024

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;


void setup() {
    Serial.begin(115200);
    ml.begin(c_model_posture);
}

void loop() {
    // pick up a random x and predict its sine
    float x = 3.14 * random(100) / 100;
    float y = sin(x);
    float input[1][3] = {{180, 170, 220}};
    float y_pred = ml.predict(input);

    // Serial.print("sin(");
    // Serial.print(x);
    // Serial.print(") = ");
    // Serial.print(y);
    Serial.print("\t predicted: ");
    Serial.println(y_pred);
    delay(1000);
}
