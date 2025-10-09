#pragma once

#include "conf/settingconf.h"
#include <string>
#include <vector>

/**
 * @brief 游戏设置类，管理如下游戏参数：游戏模式、音乐类型、当前等级、当前高度
 */
class Settings {
private:
    int m_gameTypeIdx;      // 游戏模式索引
    int m_musicTypeIdx;     // 音乐类型索引
    int m_initLevel;        // 初始等级
    int m_initHeight;       // 初始高度
    int m_newRecordOrder;   // 新纪录次序

public:
    Settings();             // 构造函数
    ~Settings() = default;  // 析构函数

    // 禁用拷贝与移动
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
    Settings(Settings&&) = delete;
    Settings& operator=(Settings&&) = delete;

    /**
     * @brief 设置游戏模式索引
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
     * @brief 设置等级
     * @param delta 索引增量（可为负数）
     * @return bool 设置成功返回 true ，否则返回 false
     */
    bool setInitLevel(int delta);
    /**
     * @brief 设置高度
     * @param delta 索引增量（可为负数）
     * @return bool 设置成功返回 true ，否则返回 false
     */
    bool setInitHeight(int delta);
    /**
     * @brief 插入新纪录
     * @param score 新纪录分数
     * @param lv 新纪录等级
     */
    void insertRecord(int score, int lv);
    /**
     * @brief 更新新纪录姓名
     * @param score 新纪录姓名
     */
    void updateRecordName(std::string name);

    /**
     * @brief 获取游戏模式索引
     * @return int 游戏模式索引
     */
    int getGameTypeIdx() const;
    /**
     * @brief 获取音乐类型索引
     * @return int 音乐类型索引
     */
    int getMusicTypeIdx() const;
    /**
     * @brief 获取初始等级
     * @return int 初始等级
     */
    int getInitLevel() const;
    /**
     * @brief 获取初始高度
     * @return int 初始高度
     */
    int getInitHeight() const;
    /**
     * @brief 获取新纪录次序
     * @return int 新纪录次序
     */
    int getNewRecordOrder() const;

    /**
     * @brief 获取游戏模式名称
     * @return std::string 游戏模式名称
     */
    std::string getGameType() const;
    /**
     * @brief 获取音乐文件名
     * @return std::string 音乐文件名
     */
    std::string getMusicPath() const;
    /**
     * @brief 获取指定排名的纪录姓名
     * @param order 排名
     * @return Record 纪录信息
     */
    Record getRecordInfo(int order) const;

private:
    /**
     * @brief 获取当前模式排行榜
     * @return Record[3] 当前模式排行榜
     */
    decltype(&RECORD_A) getCurrentRecords() const;
};