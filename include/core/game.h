#pragma once

#include "conf/gameconf.h"
#include <array>
#include <vector>

/**
 * @brief 游戏核心逻辑类，负责处理俄罗斯方块游戏的所有规则和状态
 */
class Game {
protected: 
    int m_level;        // 当前游戏等级
    int m_score;        // 当前得分
    int m_lineCount;    // 消除行数统计

    // 游戏场地数组，包含可见区域和预留高度
    std::array<std::array<TetrisStyle, TETRIS_FIELD_WIDTH>, TETRIS_FIELD_HEIGHT + TETRIS_RESERVE_HEIGHT> m_field;
    // 各种类型方块统计
    std::unordered_map<TetrisMode, int> m_tetrisCount;

    TetrisMode m_curMode;   // 当前正在下落方块类型
    TetrisMode m_nextMode;  // 下一个生成的方块类型

    std::array<std::pair<int, int>, TETRIS_NUM> m_tetrisPos;    // 当前方块中每个小方块位置
    int m_tetrisRotateStatus;                                   // 当前方块旋转状态

    std::vector<int> m_eraseLines;  // 需要消除的行索引列表

public:
    Game();                     // 构造函数
    virtual ~Game() = default;  // 析构函数

    /**
     * @brief 获取当前游戏等级
     * @return int 当前游戏等级
     */
    int getLevel() const;
    /**
     * @brief 获取当前得分
     * @return int 当前得分
     */
    int getScore() const;
    /**
     * @brief 获取当前消除行数统计
     * @return int 当前消除行数统计
     */
    int getLineCount() const;
    /**
     * @brief 获取场地指定行列样式
     * @param row 行
     * @param col 列
     * @return TetrisStyle 场地指定行列样式
     */
    TetrisStyle getFieldStyle(int row, int col) const;
    /**
     * @brief 获取指定类型方块统计
     * @param mode 方块类型
     * @return int 该类型方块统计
     */
    int getTetrisCount(TetrisMode mode) const;
    /**
     * @brief 获取当前正在下落方块类型
     * @return TetrisMode 当前正在下落方块类型
     */
    TetrisMode getCurMode() const;
    /**
     * @brief 获取下一个生成的方块类型
     * @return TetrisMode 下一个生成的方块类型
     */
    TetrisMode getNextMode() const;
    /**
     * @brief 获取当前正在下落方块最低行
     * @return int 当前正在下落方块最低行
     */
    int getTetrisLowestRow() const;

    /**
     * @brief 重置游戏
     * @param level 初始等级
     */
    void resetGame(int level);

    /**
     * @brief 生成方块
     * @return bool 生成成功返回 true ，否则返回 false
     */
    bool generate();
    /**
     * @brief 方块移动（左/右）
     * @param delta 偏移量，正数表示右移 delta 列，负数表示左移 delta 列
     * @return bool 移动成功返回 true ，否则返回 false
     */
    bool move(int delta);
    /**
     * @brief 方块旋转（顺时针/逆时针）
     * @param delta 偏移量，正数表示顺时针旋转 delta 次，负数表示逆时针旋转 delta 次
     * @return bool 旋转成功返回 true ，否则返回 false
     */
    bool rotate(int delta);
    /**
     * @brief 方块下落
     * @return bool 下落成功返回 true ，否则（触底）返回 false
     */
    bool drop();

    /**
     * @brief 统计需要消除的行
     * @return int 需要消除行数
     */
    int checkEraseLine();
    /**
     * @brief 消除需要消除的行
     * @param order 消除步骤（每行消除分六步，前五步从中间向两侧，每步消除左右各一个方块，最后一步未消除行下落）
     * @return bool 消除完毕返回 true ，否则返回 false
     */
    bool eraseComplete(int order);
    /**
     * @brief 计算得分
     * @param accelerateLineCount 不间断加速下落经历的行数
     */
    virtual void calculate(int accelerateLineCount) = 0;
};

/**
 * @brief A模式游戏逻辑类
 */
class GameA : public Game {
private:
    bool m_upgrade;     // 是否升级标志

public:
    /**
     * @brief 判断是否升级
     * @return bool 升级返回 true ，否则返回 false
     */
    bool isUpgrade() const;

    /**
     * @brief A模式特有重置逻辑
     */
    void specificReset();
    void calculate(int accelerateLineCount) override;
};

/**
 * @brief B模式游戏逻辑类
 */
class GameB : public Game {
private:
    int m_height;   // 高度

public:
    /**
     * @brief 获取当前高度
     * @return int 当前高度
     */
    int getHeight() const;

    /**
     * @brief B模式特有重置逻辑
     * @param height 初始高度
     */
    void specificReset(int height);
    void calculate(int accelerateLineCount) override;
};