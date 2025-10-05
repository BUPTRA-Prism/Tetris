#pragma once

/**
 * @brief 动画基类
 * 
 * 提供播放控制（播放/暂停/停止）、循环次数控制等通用逻辑
 *   
 * 子类只需实现 `update()` 和 `reset()`，即可定义自己的动画效果
 */
class Animation {
protected:
    bool m_playing;     // 是否正在播放
    int m_loopTarget;   // 动画循环播放上线
    int m_loopCnt;      // 当前已完成的循环次数

public:
    /**
     * @brief 构造函数
     * @param loopTarget 动画循环次数上限，-1 表示无限循环，>=0 表示动画最多执行指定次数
     */
    Animation(int loopTarget);
    virtual ~Animation() = default;     // 析构函数

    /**
     * @brief 每帧更新动画状态
     */
    void onUpdate();
    
    /**
     * @brief 播放动画
     */
    void play();
    /**
     * @brief 暂停动画
     */
    void pause();
    /**
     * @brief 停止动画
     */
    void stop();

protected:
    /**
     * @brief 动画子类需要实现的更新逻辑
     * @return 完成一个循环返回 true ，循环尚未完成返回 false  
     */
    virtual bool update() = 0;
    /**
     * @brief 动画子类需要实现的复位逻辑
     * 
     * 用于在一次循环完成后，重置动画状态
     */
    virtual void reset() = 0;
};