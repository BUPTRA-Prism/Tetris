#pragma once

#include <string>
#include <vector>

/**
 * @brief 游戏设置类（单例），管理如下游戏参数：游戏类型、音乐类型、当前关卡、当前高度
 * 
 * 使用单例模式，所有设置通过 Settings::getInstance() 访问。
 */
class Settings {
private:
    int m_curGameTypeIdx;   // 当前游戏类型索引
    int m_curMusicTypeIdx;  // 当前音乐类型索引
    int m_curLevel;         // 当前关卡
    int m_curHeight;        // 当前高度

public:
    /**
     * @brief 获取 Settings 单例
     * @return Settings& 全局唯一实例
     */
    static Settings& getInstance();

    // 禁用拷贝与移动
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
    Settings(Settings&&) = delete;
    Settings& operator=(Settings&&) = delete;

    /**
     * @brief 设置游戏类型索引
     * @param delta 索引增量（可为负数）
     * @return bool 设置成功返回 true ，否则返回 false
     */
    bool setGameType(int delta);
    /**
     * @brief 设置音乐类型索引
     * @param delta 索引增量（可为负数）
     * @return bool 设置成功返回 true ，否则返回 false
     */
    bool setMusicType(int delta);
    /**
     * @brief 设置关卡
     * @param delta 索引增量（可为负数）
     * @return bool 设置成功返回 true ，否则返回 false
     */
    bool setLevel(int delta);
    /**
     * @brief 设置高度
     * @param delta 索引增量（可为负数）
     * @return bool 设置成功返回 true ，否则返回 false
     */
    bool setHeight(int delta);

    /**
     * @brief 获取当前游戏类型索引
     * @return int 当前游戏类型索引
     */
    int getGameTypeIdx() const;
    /**
     * @brief 获取当前音乐类型索引
     * @return int 当前音乐类型索引
     */
    int getMusicTypeIdx() const;
    /**
     * @brief 获取当前关卡
     * @return int 当前关卡
     */
    int getLevel() const;
    /**
     * @brief 获取当前高度
     * @return int 当前高度
     */
    int getHeight() const;

    /**
     * @brief 获取当前游戏类型名称
     * @return std::string 当前游戏类型
     */
    std::string getGameType() const;
    /**
     * @brief 获取当前音乐文件名
     * @return std::string 当前音乐文件名
     */
    std::string getMusicPath() const;

private:
    Settings();             // 私有构造函数
    ~Settings() = default;  // 私有析构函数
};