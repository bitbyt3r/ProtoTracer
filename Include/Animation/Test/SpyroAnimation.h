#pragma once

#include "../Animation.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Objects/Spyro.h"
#include "../../Materials/NormalMaterial.h"
#include "../../Render/ObjectDeformer.h"

class SpyroAnimation : public Animation<1>{
private:
    Spyro spyro;
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 6.0f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenPersp = FunctionGenerator(FunctionGenerator::Sine, 20.0f, 250.0f, 4.0f);
    NormalMaterial nM;
    ObjectDeformer oD = ObjectDeformer(spyro.GetObject());

public:
    SpyroAnimation(){
        scene.AddObject(spyro.GetObject());

        spyro.GetObject()->SetMaterial(&nM);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        float x = fGenRotation.Update();
        float sx = fGenScale.Update();
        sx = 3.0f;
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, ratio * 720.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        spyro.GetObject()->ResetVertices();

        spyro.GetObject()->GetTransform()->SetRotation(rotation);
	    spyro.GetObject()->GetTransform()->SetScale(Vector3D(2.0f, 2.0f, 2.0f));
        spyro.GetObject()->GetTransform()->SetPosition(Vector3D(90.0f, 10.0f, 0.0f));

        spyro.GetObject()->UpdateTransform();

    }
};
