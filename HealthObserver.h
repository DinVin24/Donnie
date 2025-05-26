#pragma once

class HealthObserver {
    public:
    virtual void onHealthChange(int newHealth) = 0;
    virtual ~HealthObserver() = default;
};