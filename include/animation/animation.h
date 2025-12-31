#pragma once

class Animation {
protected:
    bool m_playing;
    int m_loopTarget;
    int m_loopCnt;

public:
    Animation(int loopTarget);
    virtual ~Animation() = default;

    void onUpdate();
    
    void play();
    void pause();
    void stop();

    bool isPlaying() const;

protected:
    virtual bool update() = 0;
    virtual void reset() = 0;
};