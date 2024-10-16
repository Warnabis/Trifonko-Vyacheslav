#ifndef ACTIVATION_H
#define ACTIVATION_H

class Activation {
public:
    virtual ~Activation() = default;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual bool isActivated() const = 0;
};

#endif
