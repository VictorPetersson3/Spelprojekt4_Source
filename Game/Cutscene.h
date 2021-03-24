#pragma once
#include "MenuObject.h"

class Cutscene :
    public MenuObject
{
public:
    Cutscene() = default;
    ~Cutscene() = default;
    void Init(const EStateType & aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
private:


};

