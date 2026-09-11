/**
 * @file rule.h
 * @brief 俄罗斯方块旋转规则，定义七种方块类型及其旋转位置偏移表
 */
#pragma once

#include <array>
#include <utility>

namespace Rule {
    /**
     * @brief 七种方块类型
     */
    enum class TetrominoType {
        T, ///< T 形
        J, ///< J 形
        Z, ///< Z 形
        O, ///< O 形（正方形）
        S, ///< S 形
        L, ///< L 形
        I  ///< I 形（长条）
    };

    /** @brief 单个方块由 4 个小格组成 */
    constexpr int BLOCK_COUNT = 4;
    /** @brief 每个方块有 4 种旋转状态 */
    constexpr int ROTATE_COUNT = 4;

    /** @brief 小格相对旋转中心的行列偏移 (row, col) */
    using BlockPosDelta = std::pair<int, int>;
    /** @brief 单一方块 4 个小格的位置偏移集合 */
    using RotatePosDelta = std::array<BlockPosDelta, BLOCK_COUNT>;
    /** @brief 某一方块 4 个旋转状态的位置偏移表 */
    using RotateData = std::array<RotatePosDelta, ROTATE_COUNT>;

    /** @brief T 形方块的旋转位置偏移表 */
    constexpr RotateData ROTATE_T = {
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 0, 2 }, BlockPosDelta{ -1, 1 } },
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 1, 1 }, BlockPosDelta{ -1, 1 } },
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 1, 1 }, BlockPosDelta{ 0, 2 } },
        RotatePosDelta{ BlockPosDelta{ 1, 1 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 1 }, BlockPosDelta{ 0, 2 } }
    };
    /** @brief J 形方块的旋转位置偏移表 */
    constexpr RotateData ROTATE_J = {
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 0, 2 }, BlockPosDelta{ -1, 2 } },
        RotatePosDelta{ BlockPosDelta{ 1, 1 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 1 }, BlockPosDelta{ -1, 0 } },
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 0, 2 }, BlockPosDelta{ 1, 0 } },
        RotatePosDelta{ BlockPosDelta{ 1, 1 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 1 }, BlockPosDelta{ 1, 2 } }
    };
    /** @brief Z 形方块的旋转位置偏移表 */
    constexpr RotateData ROTATE_Z = {
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 1 }, BlockPosDelta{ -1, 2 } },
        RotatePosDelta{ BlockPosDelta{ 1, 2 }, BlockPosDelta{ 0, 2 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 1 } },
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 1 }, BlockPosDelta{ -1, 2 } },
        RotatePosDelta{ BlockPosDelta{ 1, 2 }, BlockPosDelta{ 0, 2 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 1 } },
    };
    /** @brief O 形方块的旋转位置偏移表（旋转不变） */
    constexpr RotateData ROTATE_O = {
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 0 }, BlockPosDelta{ -1, 1 } },
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 0 }, BlockPosDelta{ -1, 1 } },
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 0 }, BlockPosDelta{ -1, 1 } },
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 0 }, BlockPosDelta{ -1, 1 } }
    };
    /** @brief S 形方块的旋转位置偏移表 */
    constexpr RotateData ROTATE_S = {
        RotatePosDelta{ BlockPosDelta{ -1, 0 }, BlockPosDelta{ -1, 1 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 0, 2 } },
        RotatePosDelta{ BlockPosDelta{ 1, 1 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 0, 2 }, BlockPosDelta{ -1, 2 } },
        RotatePosDelta{ BlockPosDelta{ -1, 0 }, BlockPosDelta{ -1, 1 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 0, 2 } },
        RotatePosDelta{ BlockPosDelta{ 1, 1 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 0, 2 }, BlockPosDelta{ -1, 2 } },
    };
    /** @brief L 形方块的旋转位置偏移表 */
    constexpr RotateData ROTATE_L = {
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 0, 2 }, BlockPosDelta{ -1, 0 } },
        RotatePosDelta{ BlockPosDelta{ 1, 1 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 1 }, BlockPosDelta{ 1, 0 } },
        RotatePosDelta{ BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 0, 2 }, BlockPosDelta{ 1, 2 } },
        RotatePosDelta{ BlockPosDelta{ 1, 1 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 1 }, BlockPosDelta{ -1, 2 } }
    };
    /** @brief I 形方块的旋转位置偏移表 */
    constexpr RotateData ROTATE_I = {
        RotatePosDelta{ BlockPosDelta{ 0, -1 }, BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 0, 2 } },
        RotatePosDelta{ BlockPosDelta{ 2, 1 }, BlockPosDelta{ 1, 1 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 1 } },
        RotatePosDelta{ BlockPosDelta{ 0, -1 }, BlockPosDelta{ 0, 0 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ 0, 2 } },
        RotatePosDelta{ BlockPosDelta{ 2, 1 }, BlockPosDelta{ 1, 1 }, BlockPosDelta{ 0, 1 }, BlockPosDelta{ -1, 1 } },
    };
}