# fast_homophones
make -f hom.mk  
make -f mvm_adt.mk

這是用 hash 方式改進搜尋速度，依據附檔字典檔，總共 134298 個單字最多蒐尋約 20 次就可找到標的  
經過測試，在搜尋 1000 個字的基準下，會比傳統 liner search 快約 1000 倍
