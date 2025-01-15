#include <gtest/gtest.h>
#include <stdio.h>
#include <sstream>
#include "../src/TextUI.h"

//測試菜單輸出
TEST(TextUITest, DisplayMenu){
    TextUI UI;

    // 擷取輸出
    testing::internal::CaptureStdout();
    UI.displayMenu();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, 
        "1. Load logic circuit file\n"
        "2. Simulation\n"
        "3. Display truth table\n"
        "4. Exit\n");
}

// 測試加載邏輯電路文件
TEST(TextUITest, LoadCircuitFile) {
    TextUI UI;

    // 測試有效文件
    EXPECT_TRUE(UI.checkFileFormat("rightFile.lcf")); // rightFile.lcf 有效文件

    // 測試無效文件
    EXPECT_FALSE(UI.checkFileFormat("invalid_path.lcf")); // 檔案不存在
    EXPECT_FALSE(UI.checkFileFormat("errorFile_1.lcf")); // 檔案格式錯誤(不合理input device)
    EXPECT_FALSE(UI.checkFileFormat("errorFile_2.lcf")); // 檔案格式錯誤(不合理字元)
    EXPECT_FALSE(UI.checkFileFormat("errorFile_3.lcf")); // 檔案格式錯誤(不合理輸入數量)
}

//測試標題輸出
TEST(TextUITest, DisplayTitle){
    //load legal file
    TextUI UI;
    std::istringstream filepath("rightFile.lcf\n");//two input one output
    std::cin.rdbuf(filepath.rdbuf());
    UI.loadFile();
    std::cin.rdbuf(nullptr);

    // 擷取輸出
    testing::internal::CaptureStdout();  
    UI.displayResultTitle();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, 
        "i i | o\n"
        "1 2 | 1\n"
        "----+--\n");
}

// 測試模擬功能
TEST(TextUITest, Simulation) {
    //load legal file
    TextUI UI;
    std::istringstream filepath("rightFile.lcf\n");//one AND Gate
    std::cin.rdbuf(filepath.rdbuf());
    UI.loadFile();
    std::cin.rdbuf(nullptr);
    
    // 提供輸入並驗證輸出
    std::istringstream inputValue("1\n0\n");
    std::cin.rdbuf(inputValue.rdbuf());
    // 擷取輸出
    testing::internal::CaptureStdout();
    UI.simulation();
    std::string out = testing::internal::GetCapturedStdout();
    
    std::cin.rdbuf(nullptr);
    
    EXPECT_EQ(out, 
        "Please key in the value of input pin 1:"
        "Please key in the value of input pin 2:"
        "Simulation Result:\n"
        "i i | o\n"
        "1 2 | 1\n"
        "----+--\n"
        "1 0 | 0\n");
}


// 測試真值表生成
TEST(TextUITest, TruthTable) {
    //load legal file
    TextUI UI;
    std::istringstream filepath("rightFile.lcf\n");
    std::cin.rdbuf(filepath.rdbuf());
    UI.loadFile();
    std::cin.rdbuf(nullptr);

    // 擷取輸出
    testing::internal::CaptureStdout();
    UI.displayTruthTable();
    std::string out = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(out, 
        "Truth table:\n"
        "i i | o\n"
        "1 2 | 1\n"
        "----+--\n"
        "0 0 | 0\n"
        "0 1 | 0\n"
        "1 0 | 0\n"
        "1 1 | 1\n");
}

// 測試異常處理
TEST(TextUITest, ErrorHandling) {
    TextUI UI;

    // 加載前執行模擬
    testing::internal::CaptureStdout();
    UI.simulation();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, "Please load an lcf file, before using this operation.\n");

    // 加載前請求真值表
    testing::internal::CaptureStdout();
    UI.displayTruthTable();
    out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, "Please load an lcf file, before using this operation.\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
