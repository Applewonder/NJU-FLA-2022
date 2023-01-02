#Q = {0,add,start_mul,mul,mul_move,mul_back,test_back,test,pre_add,1_res,true_1,true_2,true_3,true_4,halt,0_res,false_1,false_2,false_3,false_4,false_5}
#S = {1}
#G = {1,_,t,r,u,e,f,a,l,s}
#q0 = 0
#B = _
#F = {halt}
#N = 4
0 1___ 1___ **** add
add 1___ 111_ **** start_mul
add 1__1 1111 **** start_mul
start_mul 111_ 111_ *ll* start_mul
start_mul 1111 1111 *ll* start_mul
start_mul 1___ 1___ *rr* mul
start_mul 1__1 1__1 *rr* mul
mul 111_ 1111 **rr mul
mul 1111 1111 **rr mul
mul 11__ 11__ *r** mul_move
mul 11_1 11_1 *r** mul_move
mul_move 11__ 11__ **l* mul_back
mul_move 11_1 11_1 **l* mul_back
mul_back 111_ 111_ **l* mul_back
mul_back 1111 1111 **l* mul_back
mul_back 11_1 11_1 **r* mul
mul_back 11__ 11__ **r* mul
mul_move 1___ 1___ ***l test_back
test_back 1__1 1__1 ***l test_back
test_back 1___ 1___ ***r test
test 1__1 1__1 r**r test
test 1___ 1___ l**l pre_add
pre_add 1__1 1__1 l**l pre_add
pre_add ____ ____ r**r add
test ____ ____ l*** 1_res
1_res 1___ ____ l*** 1_res
1_res ____ ____ r*** true_1
true_1 ____ t___ r*** true_2
true_2 ____ r___ r*** true_3
true_3 ____ u___ r*** true_4
true_4 ____ e___ **** halt
test ___1 ___1 l*** 0_res
0_res 1__1 ___1 l*** 0_res
0_res ___1 ___1 r*** false_1
false_1 ___1 f__1 r*** false_2
false_2 ___1 a__1 r*** false_3
false_3 ___1 l__1 r*** false_4
false_4 ___1 s__1 r*** false_5
false_5 ___1 e__1 **** halt