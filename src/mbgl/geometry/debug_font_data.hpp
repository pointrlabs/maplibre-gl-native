// This is an implementation file, so omit include guards.

#include <cstdint>
#include <map>

const int8_t simplex_1[] = {5, 21, 5, 7, -1, -1, 5, 2, 4, 1, 5, 0, 6, 1, 5, 2};
const int8_t simplex_2[] = {4, 21, 4, 14, -1, -1, 12, 21, 12, 14};
const int8_t simplex_3[] = {11, 25, 4, -7, -1, -1, 17, 25, 10, -7, -1, -1, 4, 12, 18, 12, -1, -1, 3, 6, 17, 6};
const int8_t simplex_4[] = {8,  25, 8,  -4, -1, -1, 12, 25, 12, -4, -1, -1, 17, 18, 15, 20, 12, 21,
                            8,  21, 5,  20, 3,  18, 3,  16, 4,  14, 5,  13, 7,  12, 13, 10, 15, 9,
                            16, 8,  17, 6,  17, 3,  15, 1,  12, 0,  8,  0,  5,  1,  3,  3};
const int8_t simplex_5[] = {21, 21, 3,  0, -1, -1, 8,  21, 10, 19, 10, 17, 9,  15, 7,  14, 5,  14, 3,  16, 3,
                            18, 4,  20, 6, 21, 8,  21, 10, 20, 13, 19, 16, 19, 19, 20, 21, 21, -1, -1, 17, 7,
                            15, 6,  14, 4, 14, 2,  16, 0,  18, 0,  20, 1,  21, 3,  21, 5,  19, 7,  17, 7};
const int8_t simplex_6[] = {23, 12, 23, 13, 22, 14, 21, 14, 20, 13, 19, 11, 17, 6,  15, 3,  13, 1,  11, 0,  7,  0,  5,
                            1,  4,  2,  3,  4,  3,  6,  4,  8,  5,  9,  12, 13, 13, 14, 14, 16, 14, 18, 13, 20, 11, 21,
                            9,  20, 8,  18, 8,  16, 9,  13, 11, 10, 16, 3,  18, 1,  20, 0,  22, 0,  23, 1,  23, 2};
const int8_t simplex_7[] = {5, 19, 4, 20, 5, 21, 6, 20, 6, 18, 5, 16, 4, 15};
const int8_t simplex_8[] = {11, 25, 9, 23, 7, 20, 5, 16, 4, 11, 4, 7, 5, 2, 7, -2, 9, -5, 11, -7};
const int8_t simplex_9[] = {3, 25, 5, 23, 7, 20, 9, 16, 10, 11, 10, 7, 9, 2, 7, -2, 5, -5, 3, -7};
const int8_t simplex_10[] = {8, 21, 8, 9, -1, -1, 3, 18, 13, 12, -1, -1, 13, 18, 3, 12};
const int8_t simplex_11[] = {13, 18, 13, 0, -1, -1, 4, 9, 22, 9};
const int8_t simplex_12[] = {6, 1, 5, 0, 4, 1, 5, 2, 6, 1, 6, -1, 5, -3, 4, -4};
const int8_t simplex_13[] = {4, 9, 22, 9};
const int8_t simplex_14[] = {5, 2, 4, 1, 5, 0, 6, 1, 5, 2};
const int8_t simplex_15[] = {20, 25, 2, -7};
const int8_t simplex_16[] = {9, 21, 6, 20, 4, 17, 3, 12, 3,  9,  4,  4,  6,  1,  9,  0, 11,
                             0, 14, 1, 16, 4, 17, 9, 17, 12, 16, 17, 14, 20, 11, 21, 9, 21};
const int8_t simplex_17[] = {6, 17, 8, 18, 11, 21, 11, 0};
const int8_t simplex_18[] = {4,  16, 4,  17, 5,  19, 6,  20, 8,  21, 12, 21, 14, 20,
                             15, 19, 16, 17, 16, 15, 15, 13, 13, 10, 3,  0,  17, 0};
const int8_t simplex_19[] = {5, 21, 16, 21, 10, 13, 13, 13, 15, 12, 16, 11, 17, 8, 17,
                             6, 16, 3,  14, 1,  11, 0,  8,  0,  5,  1,  4,  2,  3, 4};
const int8_t simplex_20[] = {13, 21, 3, 7, 18, 7, -1, -1, 13, 21, 13, 0};
const int8_t simplex_21[] = {15, 21, 5, 21, 4, 12, 5, 13, 8, 14, 11, 14, 14, 13, 16, 11, 17,
                             8,  17, 6, 16, 3, 14, 1, 11, 0, 8,  0,  5,  1,  4,  2,  3,  4};
const int8_t simplex_22[] = {16, 18, 15, 20, 12, 21, 10, 21, 7, 20, 5,  17, 4,  12, 4,  7,  5,  3, 7,  1, 10, 0, 11,
                             0,  14, 1,  16, 3,  17, 6,  17, 7, 16, 10, 14, 12, 11, 13, 10, 13, 7, 12, 5, 10, 4, 7};
const int8_t simplex_23[] = {17, 21, 7, 0, -1, -1, 3, 21, 17, 21};
const int8_t simplex_24[] = {8,  21, 5,  20, 4,  18, 4,  16, 5,  14, 7,  13, 11, 12, 14, 11, 16, 9, 17, 7,
                             17, 4,  16, 2,  15, 1,  12, 0,  8,  0,  5,  1,  4,  2,  3,  4,  3,  7, 4,  9,
                             6,  11, 9,  12, 13, 13, 15, 14, 16, 16, 16, 18, 15, 20, 12, 21, 8,  21};
const int8_t simplex_25[] = {16, 14, 15, 11, 13, 9,  10, 8,  9,  8,  6, 9,  4, 11, 3, 14, 3, 15, 4, 18, 6, 20, 9,
                             21, 10, 21, 13, 20, 15, 18, 16, 14, 16, 9, 15, 4, 13, 1, 10, 0, 8,  0, 5,  1, 4,  3};
const int8_t simplex_26[] = {5, 14, 4, 13, 5, 12, 6, 13, 5, 14, -1, -1, 5, 2, 4, 1, 5, 0, 6, 1, 5, 2};
const int8_t simplex_27[] = {5, 14, 4, 13, 5, 12, 6, 13, 5, 14, -1, -1, 6, 1,
                             5, 0,  4, 1,  5, 2,  6, 1,  6, -1, 5,  -3, 4, -4};
const int8_t simplex_28[] = {20, 18, 4, 9, 20, 0};
const int8_t simplex_29[] = {4, 12, 22, 12, -1, -1, 4, 6, 22, 6};
const int8_t simplex_30[] = {4, 18, 20, 9, 4, 0};
const int8_t simplex_31[] = {3,  16, 3,  17, 4, 19, 5, 20, 7,  21, 11, 21, 13, 20, 14, 19, 15, 17, 15, 15,
                             14, 13, 13, 12, 9, 10, 9, 7,  -1, -1, 9,  2,  8,  1,  9,  0,  10, 1,  9,  2};
const int8_t simplex_32[] = {18, 13, 17, 15, 15, 16, 12, 16, 10, 15, 9,  14, 8,  11, 8,  8,  9,  6,  11, 5,  14, 5,
                             16, 6,  17, 8,  -1, -1, 12, 16, 10, 14, 9,  11, 9,  8,  10, 6,  11, 5,  -1, -1, 18, 16,
                             17, 8,  17, 6,  19, 5,  21, 5,  23, 7,  24, 10, 24, 12, 23, 15, 22, 17, 20, 19, 18, 20,
                             15, 21, 12, 21, 9,  20, 7,  19, 5,  17, 4,  15, 3,  12, 3,  9,  4,  6,  5,  4,  7,  2,
                             9,  1,  12, 0,  15, 0,  18, 1,  20, 2,  21, 3,  -1, -1, 19, 16, 18, 8,  18, 6,  19, 5};
const int8_t simplex_33[] = {9, 21, 1, 0, -1, -1, 9, 21, 17, 0, -1, -1, 4, 7, 14, 7};
const int8_t simplex_34[] = {4,  21, 4,  0, -1, -1, 4,  21, 13, 21, 16, 20, 17, 19, 18, 17, 18, 15, 17, 13, 16, 12, 13,
                             11, -1, -1, 4, 11, 13, 11, 16, 10, 17, 9,  18, 7,  18, 4,  17, 2,  16, 1,  13, 0,  4,  0};
const int8_t simplex_35[] = {18, 16, 17, 18, 15, 20, 13, 21, 9, 21, 7,  20, 5,  18, 4,  16, 3,  13,
                             3,  8,  4,  5,  5,  3,  7,  1,  9, 0,  13, 0,  15, 1,  17, 3,  18, 5};
const int8_t simplex_36[] = {4,  21, 4,  0,  -1, -1, 4, 21, 11, 21, 14, 20, 16, 18, 17,
                             16, 18, 13, 18, 8,  17, 5, 16, 3,  14, 1,  11, 0,  4,  0};
const int8_t simplex_37[] = {4, 21, 4, 0, -1, -1, 4, 21, 17, 21, -1, -1, 4, 11, 12, 11, -1, -1, 4, 0, 17, 0};
const int8_t simplex_38[] = {4, 21, 4, 0, -1, -1, 4, 21, 17, 21, -1, -1, 4, 11, 12, 11};
const int8_t simplex_39[] = {18, 16, 17, 18, 15, 20, 13, 21, 9,  21, 7,  20, 5,  18, 4,  16, 3,  13, 3,  8, 4,  5,
                             5,  3,  7,  1,  9,  0,  13, 0,  15, 1,  17, 3,  18, 5,  18, 8,  -1, -1, 13, 8, 18, 8};
const int8_t simplex_40[] = {4, 21, 4, 0, -1, -1, 18, 21, 18, 0, -1, -1, 4, 11, 18, 11};
const int8_t simplex_41[] = {4, 21, 4, 0};
const int8_t simplex_42[] = {12, 21, 12, 5, 11, 2, 10, 1, 8, 0, 6, 0, 4, 1, 3, 2, 2, 5, 2, 7};
const int8_t simplex_43[] = {4, 21, 4, 0, -1, -1, 18, 21, 4, 7, -1, -1, 9, 12, 18, 0};
const int8_t simplex_44[] = {4, 21, 4, 0, -1, -1, 4, 0, 16, 0};
const int8_t simplex_45[] = {4, 21, 4, 0, -1, -1, 4, 21, 12, 0, -1, -1, 20, 21, 12, 0, -1, -1, 20, 21, 20, 0};
const int8_t simplex_46[] = {4, 21, 4, 0, -1, -1, 4, 21, 18, 0, -1, -1, 18, 21, 18, 0};
const int8_t simplex_47[] = {9, 21, 7, 20, 5, 18, 4, 16, 3, 13, 3,  8,  4,  5,  5,  3,  7,  1,  9,  0, 13,
                             0, 15, 1, 17, 3, 18, 5, 19, 8, 19, 13, 18, 16, 17, 18, 15, 20, 13, 21, 9, 21};
const int8_t simplex_48[] = {4,  21, 4,  0,  -1, -1, 4,  21, 13, 21, 16, 20, 17,
                             19, 18, 17, 18, 14, 17, 12, 16, 11, 13, 10, 4,  10};
const int8_t simplex_49[] = {9,  21, 7,  20, 5,  18, 4,  16, 3,  13, 3,  8,  4,  5, 5,  3,
                             7,  1,  9,  0,  13, 0,  15, 1,  17, 3,  18, 5,  19, 8, 19, 13,
                             18, 16, 17, 18, 15, 20, 13, 21, 9,  21, -1, -1, 12, 4, 18, -2};
const int8_t simplex_50[] = {4,  21, 4,  0,  -1, -1, 4,  21, 13, 21, 16, 20, 17, 19, 18, 17,
                             18, 15, 17, 13, 16, 12, 13, 11, 4,  11, -1, -1, 11, 11, 18, 0};
const int8_t simplex_51[] = {17, 18, 15, 20, 12, 21, 8,  21, 5,  20, 3,  18, 3,  16, 4, 14, 5, 13, 7, 12,
                             13, 10, 15, 9,  16, 8,  17, 6,  17, 3,  15, 1,  12, 0,  8, 0,  5, 1,  3, 3};
const int8_t simplex_52[] = {8, 21, 8, 0, -1, -1, 1, 21, 15, 21};
const int8_t simplex_53[] = {4, 21, 4, 6, 5, 3, 7, 1, 10, 0, 12, 0, 15, 1, 17, 3, 18, 6, 18, 21};
const int8_t simplex_54[] = {1, 21, 9, 0, -1, -1, 17, 21, 9, 0};
const int8_t simplex_55[] = {2, 21, 7, 0, -1, -1, 12, 21, 7, 0, -1, -1, 12, 21, 17, 0, -1, -1, 22, 21, 17, 0};
const int8_t simplex_56[] = {3, 21, 17, 0, -1, -1, 17, 21, 3, 0};
const int8_t simplex_57[] = {1, 21, 9, 11, 9, 0, -1, -1, 17, 21, 9, 11};
const int8_t simplex_58[] = {17, 21, 3, 0, -1, -1, 3, 21, 17, 21, -1, -1, 3, 0, 17, 0};
const int8_t simplex_59[] = {4, 25, 4, -7, -1, -1, 5, 25, 5, -7, -1, -1, 4, 25, 11, 25, -1, -1, 4, -7, 11, -7};
const int8_t simplex_60[] = {0, 21, 14, -3};
const int8_t simplex_61[] = {9, 25, 9, -7, -1, -1, 10, 25, 10, -7, -1, -1, 3, 25, 10, 25, -1, -1, 3, -7, 10, -7};
const int8_t simplex_62[] = {6, 15, 8, 18, 10, 15, -1, -1, 3, 12, 8, 17, 13, 12, -1, -1, 8, 17, 8, 0};
const int8_t simplex_63[] = {0, -2, 16, -2};
const int8_t simplex_64[] = {6, 21, 5, 20, 4, 18, 4, 16, 5, 15, 6, 16, 5, 17};
const int8_t simplex_65[] = {15, 14, 15, 0, -1, -1, 15, 11, 13, 13, 11, 14, 8, 14, 6, 13, 4,
                             11, 3,  8,  3, 6,  4,  3,  6,  1,  8,  0,  11, 0, 13, 1, 15, 3};
const int8_t simplex_66[] = {4,  21, 4, 0,  -1, -1, 4, 11, 6, 13, 8, 14, 11, 14, 13, 13, 15,
                             11, 16, 8, 16, 6,  15, 3, 13, 1, 11, 0, 8,  0,  6,  1,  4,  3};
const int8_t simplex_67[] = {15, 11, 13, 13, 11, 14, 8, 14, 6,  13, 4,  11, 3,  8,
                             3,  6,  4,  3,  6,  1,  8, 0,  11, 0,  13, 1,  15, 3};
const int8_t simplex_68[] = {15, 21, 15, 0, -1, -1, 15, 11, 13, 13, 11, 14, 8, 14, 6, 13, 4,
                             11, 3,  8,  3, 6,  4,  3,  6,  1,  8,  0,  11, 0, 13, 1, 15, 3};
const int8_t simplex_69[] = {3,  8, 15, 8, 15, 10, 14, 12, 13, 13, 11, 14, 8, 14, 6, 13, 4,
                             11, 3, 8,  3, 6,  4,  3,  6,  1,  8,  0,  11, 0, 13, 1, 15, 3};
const int8_t simplex_70[] = {10, 21, 8, 21, 6, 20, 5, 17, 5, 0, -1, -1, 2, 14, 9, 14};
const int8_t simplex_71[] = {15, 14, 15, -2, 14, -5, 13, -6, 11, -7, 8, -7, 6, -6, -1, -1, 15, 11, 13, 13, 11, 14,
                             8,  14, 6,  13, 4,  11, 3,  8,  3,  6,  4, 3,  6, 1,  8,  0,  11, 0,  13, 1,  15, 3};
const int8_t simplex_72[] = {4, 21, 4, 0, -1, -1, 4, 10, 7, 13, 9, 14, 12, 14, 14, 13, 15, 10, 15, 0};
const int8_t simplex_73[] = {3, 21, 4, 20, 5, 21, 4, 22, 3, 21, -1, -1, 4, 14, 4, 0};
const int8_t simplex_74[] = {5, 21, 6, 20, 7, 21, 6, 22, 5, 21, -1, -1, 6, 14, 6, -3, 5, -6, 3, -7, 1, -7};
const int8_t simplex_75[] = {4, 21, 4, 0, -1, -1, 14, 14, 4, 4, -1, -1, 8, 8, 15, 0};
const int8_t simplex_76[] = {4, 21, 4, 0};
const int8_t simplex_77[] = {4,  14, 4,  0,  -1, -1, 4,  10, 7,  13, 9,  14, 12, 14, 14, 13, 15, 10,
                             15, 0,  -1, -1, 15, 10, 18, 13, 20, 14, 23, 14, 25, 13, 26, 10, 26, 0};
const int8_t simplex_78[] = {4, 14, 4, 0, -1, -1, 4, 10, 7, 13, 9, 14, 12, 14, 14, 13, 15, 10, 15, 0};
const int8_t simplex_79[] = {8, 14, 6, 13, 4, 11, 3, 8,  3, 6,  4,  3,  6,  1,  8,  0, 11,
                             0, 13, 1, 15, 3, 16, 6, 16, 8, 15, 11, 13, 13, 11, 14, 8, 14};
const int8_t simplex_80[] = {4,  14, 4, -7, -1, -1, 4, 11, 6, 13, 8, 14, 11, 14, 13, 13, 15,
                             11, 16, 8, 16, 6,  15, 3, 13, 1, 11, 0, 8,  0,  6,  1,  4,  3};
const int8_t simplex_81[] = {15, 14, 15, -7, -1, -1, 15, 11, 13, 13, 11, 14, 8, 14, 6, 13, 4,
                             11, 3,  8,  3,  6,  4,  3,  6,  1,  8,  0,  11, 0, 13, 1, 15, 3};
const int8_t simplex_82[] = {4, 14, 4, 0, -1, -1, 4, 8, 5, 11, 7, 13, 9, 14, 12, 14};
const int8_t simplex_83[] = {14, 11, 13, 13, 10, 14, 7, 14, 4, 13, 3, 11, 4, 9, 6, 8, 11,
                             7,  13, 6,  14, 4,  14, 3, 13, 1, 10, 0, 7,  0, 4, 1, 3, 3};
const int8_t simplex_84[] = {5, 21, 5, 4, 6, 1, 8, 0, 10, 0, -1, -1, 2, 14, 9, 14};
const int8_t simplex_85[] = {4, 14, 4, 4, 5, 1, 7, 0, 10, 0, 12, 1, 15, 4, -1, -1, 15, 14, 15, 0};
const int8_t simplex_86[] = {2, 14, 8, 0, -1, -1, 14, 14, 8, 0};
const int8_t simplex_87[] = {3, 14, 7, 0, -1, -1, 11, 14, 7, 0, -1, -1, 11, 14, 15, 0, -1, -1, 19, 14, 15, 0};
const int8_t simplex_88[] = {3, 14, 14, 0, -1, -1, 14, 14, 3, 0};
const int8_t simplex_89[] = {2, 14, 8, 0, -1, -1, 14, 14, 8, 0, 6, -4, 4, -6, 2, -7, 1, -7};
const int8_t simplex_90[] = {14, 14, 3, 0, -1, -1, 3, 14, 14, 14, -1, -1, 3, 0, 14, 0};
const int8_t simplex_91[] = {9,  25, 7, 24, 6, 23, 5, 21, 5, 19, 6, 17, 7, 16, 8, 14, 8,  12, 6, 10,
                             -1, -1, 7, 24, 6, 22, 6, 20, 7, 18, 8, 17, 9, 15, 9, 13, 8,  11, 4, 9,
                             8,  7,  9, 5,  9, 3,  8, 1,  7, 0,  6, -2, 6, -4, 7, -6, -1, -1, 6, 8,
                             8,  6,  8, 4,  7, 2,  6, 1,  5, -1, 5, -3, 6, -5, 7, -6, 9,  -7};
const int8_t simplex_92[] = {4, 25, 4, -7};
const int8_t simplex_93[] = {5,  25, 7, 24, 8, 23, 9, 21, 9, 19, 8, 17, 7, 16, 6, 14, 6,  12, 8,  10,
                             -1, -1, 7, 24, 8, 22, 8, 20, 7, 18, 6, 17, 5, 15, 5, 13, 6,  11, 10, 9,
                             6,  7,  5, 5,  5, 3,  6, 1,  7, 0,  8, -2, 8, -4, 7, -6, -1, -1, 8,  8,
                             6,  6,  6, 4,  7, 2,  8, 1,  9, -1, 9, -3, 8, -5, 7, -6, 5,  -7};
const int8_t simplex_94[] = {3,  6, 3, 8, 4,  11, 6,  12, 8,  12, 10, 11, 14, 8,  16, 7,  18, 7,  20, 8,  21, 10, -1,
                             -1, 3, 8, 4, 10, 6,  11, 8,  11, 10, 10, 14, 7,  16, 6,  18, 6,  20, 7,  21, 10, 21, 12};

struct glyph {
    uint8_t width;
    uint8_t length;
    const int8_t *data;
};

// Font data From Hershey Simplex Font
// http://paulbourke.net/dataformats/hershey/

const glyph simplex[] = {
    /* 32	  */ {16, 0, nullptr},
    /* 33	! */
    {10, sizeof(simplex_1), simplex_1},
    /* 34	" */
    {16, sizeof(simplex_2), simplex_2},
    /* 35	# */
    {21, sizeof(simplex_3), simplex_3},
    /* 36	$ */
    {20, sizeof(simplex_4), simplex_4},
    /* 37	% */
    {24, sizeof(simplex_5), simplex_5},
    /* 38	& */
    {26, sizeof(simplex_6), simplex_6},
    /* 39	' */
    {10, sizeof(simplex_7), simplex_7},
    /* 40	( */
    {14, sizeof(simplex_8), simplex_8},
    /* 41	) */
    {14, sizeof(simplex_9), simplex_9},
    /* 42	* */
    {16, sizeof(simplex_10), simplex_10},
    /* 43	+ */
    {26, sizeof(simplex_11), simplex_11},
    /* 44	, */
    {10, sizeof(simplex_12), simplex_12},
    /* 45	- */
    {26, sizeof(simplex_13), simplex_13},
    /* 46	. */
    {10, sizeof(simplex_14), simplex_14},
    /* 47	/ */
    {22, sizeof(simplex_15), simplex_15},
    /* 48	0 */
    {20, sizeof(simplex_16), simplex_16},
    /* 49	1 */
    {20, sizeof(simplex_17), simplex_17},
    /* 50	2 */
    {20, sizeof(simplex_18), simplex_18},
    /* 51	3 */
    {20, sizeof(simplex_19), simplex_19},
    /* 52	4 */
    {20, sizeof(simplex_20), simplex_20},
    /* 53	5 */
    {20, sizeof(simplex_21), simplex_21},
    /* 54	6 */
    {20, sizeof(simplex_22), simplex_22},
    /* 55	7 */
    {20, sizeof(simplex_23), simplex_23},
    /* 56	8 */
    {20, sizeof(simplex_24), simplex_24},
    /* 57	9 */
    {20, sizeof(simplex_25), simplex_25},
    /* 58	: */
    {10, sizeof(simplex_26), simplex_26},
    /* 59	; */
    {10, sizeof(simplex_27), simplex_27},
    /* 60	< */
    {24, sizeof(simplex_28), simplex_28},
    /* 61	= */
    {26, sizeof(simplex_29), simplex_29},
    /* 62	> */
    {24, sizeof(simplex_30), simplex_30},
    /* 63	? */
    {18, sizeof(simplex_31), simplex_31},
    /* 64	@ */
    {27, sizeof(simplex_32), simplex_32},
    /* 65	A */
    {18, sizeof(simplex_33), simplex_33},
    /* 66	B */
    {21, sizeof(simplex_34), simplex_34},
    /* 67	C */
    {21, sizeof(simplex_35), simplex_35},
    /* 68	D */
    {21, sizeof(simplex_36), simplex_36},
    /* 69	E */
    {19, sizeof(simplex_37), simplex_37},
    /* 70	F */
    {18, sizeof(simplex_38), simplex_38},
    /* 71	G */
    {21, sizeof(simplex_39), simplex_39},
    /* 72	H */
    {22, sizeof(simplex_40), simplex_40},
    /* 73	I */
    {8, sizeof(simplex_41), simplex_41},
    /* 74	J */
    {16, sizeof(simplex_42), simplex_42},
    /* 75	K */
    {21, sizeof(simplex_43), simplex_43},
    /* 76	L */
    {17, sizeof(simplex_44), simplex_44},
    /* 77	M */
    {24, sizeof(simplex_45), simplex_45},
    /* 78	N */
    {22, sizeof(simplex_46), simplex_46},
    /* 79	O */
    {22, sizeof(simplex_47), simplex_47},
    /* 80	P */
    {21, sizeof(simplex_48), simplex_48},
    /* 81	Q */
    {22, sizeof(simplex_49), simplex_49},
    /* 82	R */
    {21, sizeof(simplex_50), simplex_50},
    /* 83	S */
    {20, sizeof(simplex_51), simplex_51},
    /* 84	T */
    {16, sizeof(simplex_52), simplex_52},
    /* 85	U */
    {22, sizeof(simplex_53), simplex_53},
    /* 86	V */
    {18, sizeof(simplex_54), simplex_54},
    /* 87	W */
    {24, sizeof(simplex_55), simplex_55},
    /* 88	X */
    {20, sizeof(simplex_56), simplex_56},
    /* 89	Y */
    {18, sizeof(simplex_57), simplex_57},
    /* 90	Z */
    {20, sizeof(simplex_58), simplex_58},
    /* 91	[ */
    {14, sizeof(simplex_59), simplex_59},
    /* 92	\ */
    {14, sizeof(simplex_60), simplex_60},
    /* 93	] */
    {14, sizeof(simplex_61), simplex_61},
    /* 94	^ */
    {16, sizeof(simplex_62), simplex_62},
    /* 95	_ */
    {16, sizeof(simplex_63), simplex_63},
    /* 96	` */
    {10, sizeof(simplex_64), simplex_64},
    /* 97	a */
    {19, sizeof(simplex_65), simplex_65},
    /* 98	b */
    {19, sizeof(simplex_66), simplex_66},
    /* 99	c */
    {18, sizeof(simplex_67), simplex_67},
    /* 100	d */
    {19, sizeof(simplex_68), simplex_68},
    /* 101	e */
    {18, sizeof(simplex_69), simplex_69},
    /* 102	f */
    {12, sizeof(simplex_70), simplex_70},
    /* 103	g */
    {19, sizeof(simplex_71), simplex_71},
    /* 104	h */
    {19, sizeof(simplex_72), simplex_72},
    /* 105	i */
    {8, sizeof(simplex_73), simplex_73},
    /* 106	j */
    {10, sizeof(simplex_74), simplex_74},
    /* 107	k */
    {17, sizeof(simplex_75), simplex_75},
    /* 108	l */
    {8, sizeof(simplex_76), simplex_76},
    /* 109	m */
    {30, sizeof(simplex_77), simplex_77},
    /* 110	n */
    {19, sizeof(simplex_78), simplex_78},
    /* 111	o */
    {19, sizeof(simplex_79), simplex_79},
    /* 112	p */
    {19, sizeof(simplex_80), simplex_80},
    /* 113	q */
    {19, sizeof(simplex_81), simplex_81},
    /* 114	r */
    {13, sizeof(simplex_82), simplex_82},
    /* 115	s */
    {17, sizeof(simplex_83), simplex_83},
    /* 116	t */
    {12, sizeof(simplex_84), simplex_84},
    /* 117	u */
    {19, sizeof(simplex_85), simplex_85},
    /* 118	v */
    {16, sizeof(simplex_86), simplex_86},
    /* 119	w */
    {22, sizeof(simplex_87), simplex_87},
    /* 120	x */
    {17, sizeof(simplex_88), simplex_88},
    /* 121	y */
    {16, sizeof(simplex_89), simplex_89},
    /* 122	z */
    {17, sizeof(simplex_90), simplex_90},
    /* 123	{ */
    {14, sizeof(simplex_91), simplex_91},
    /* 124	| */
    {8, sizeof(simplex_92), simplex_92},
    /* 125	} */
    {14, sizeof(simplex_93), simplex_93},
    /* 126	~ */
    {24, sizeof(simplex_94), simplex_94},
};