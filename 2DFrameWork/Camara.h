#pragma once
class Camera : public Singleton<Camera>
{
private:
    Viewport            viewport;  
    Matrix              V, P, VP, S;

public:
    //카메라위치
    Vector2             position;
    Vector2             scale=Vector2(1.0f,1.0f);
public:
    Camera();
    void          Set();
    void          ResizeScreen();
    const Matrix& GetP() { return P; };
    const Matrix& GetVP() { return VP; };
};