#include <gtest/gtest.h>
#include "../src/LogicSimulator.h" // 假設您實作了 LogicSimulator 類別

// 測試加載邏輯電路文件
TEST(LogicSimulatorTest, LoadCircuitFile) {
    LogicSimulator ls;

    // 測試有效文件
    EXPECT_TRUE(ls.load("rightFile.lcf")); // test_circuit1.lcf 是一個有效的電路文件

    // 測試無效文件
    EXPECT_FALSE(ls.load("invalid_path.lcf")); // 檔案不存在
    EXPECT_FALSE(ls.load("invalid_format.lcf")); // 檔案格式錯誤
}

// 測試模擬功能
TEST(LogicSimulatorTest, Simulation) {
    LogicSimulator ls;
    ls.load("test_circuit1.lcf"); // 預載入有效電路文件

    // 提供輸入並驗證輸出
    std::vector<int> inputs = {0, 1, 1}; // 假設電路有 3 個輸入
    std::string result = ls.getSimulationResult(inputs);
    EXPECT_EQ(result, "Simulation Result: 0 1 1 | 0"); // 預期結果
}

// 測試真值表生成
TEST(LogicSimulatorTest, TruthTable) {
    LogicSimulator ls;
    ls.load("test_circuit1.lcf"); // 預載入有效電路文件

    std::string truthTable = ls.getTruthTable();
    EXPECT_EQ(truthTable, 
        "i i i | o\n"
        "1 2 3 | 1\n"
        "------+--\n"
        "0 0 0 | 0\n"
        "0 0 1 | 0\n"
        "0 1 0 | 0\n"
        "0 1 1 | 0\n"
        "1 0 0 | 1\n"
        "1 0 1 | 1\n"
        "1 1 0 | 0\n"
        "1 1 1 | 0\n");
}

// 測試異常處理
TEST(LogicSimulatorTest, ErrorHandling) {
    LogicSimulator ls;

    // 加載前執行模擬
    EXPECT_THROW(ls.getSimulationResult({1, 0, 1}), std::runtime_error);

    // 加載前請求真值表
    EXPECT_THROW(ls.getTruthTable(), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
