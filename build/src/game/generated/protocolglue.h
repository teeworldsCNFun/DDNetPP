#ifndef GAME_GENERATED_PROTOCOLGLUE
#define GAME_GENERATED_PROTOCOLGLUE
static const int gs_Msg_SixToSeven[38] = {
0,1,2,3,5,-1,6,7,8,9,10,11,12,13,14,15,16,24,25,26,27,-1,28,30,31,32,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
};
inline int Msg_SixToSeven(int a) { if(a < 0 || a >= 38) return -1; return gs_Msg_SixToSeven[a]; }
static const int gs_Msg_SevenToSix[40] = {
0,1,2,3,-1,4,6,7,8,9,10,11,12,13,14,15,16,-1,-1,-1,-1,-1,-1,-1,17,18,19,20,22,-1,23,24,25,-1,-1,-1,-1,-1,-1,-1
};
inline int Msg_SevenToSix(int a) { if(a < 0 || a >= 40) return -1; return gs_Msg_SevenToSix[a]; }
static const int gs_Obj_SixToSeven[21] = {
0,1,2,3,4,5,-1,6,9,10,11,-1,12,16,17,18,19,20,-1,21,-1
};
inline int Obj_SixToSeven(int a) { if(a < 0 || a >= 21) return -1; return gs_Obj_SixToSeven[a]; }
static const int gs_Obj_SevenToSix[25] = {
0,1,2,3,4,5,7,-1,-1,8,9,10,12,-1,-1,-1,13,14,15,16,17,19,-1,-1,-1
};
inline int Obj_SevenToSix(int a) { if(a < 0 || a >= 25) return -1; return gs_Obj_SevenToSix[a]; }
#endif //GAME_GENERATED_PROTOCOLGLUE
