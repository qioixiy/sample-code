#pragma once

class Graphics {
    virtual void DrawLine();

    virtual void DrawRect();
    virtual void FillRect();

    virtual void DrawOval();
    virtual void FillOval();

    virtual void DrawArc();

    virtual void DrawPolygon();

    virtual void DrawString();

    virtual void DrawImage();
};
