echo "\n//////// Norming fdf\n"
norminette ./*.c ./*.h 
echo "\n//////// Norming libft\n"
norminette ./libft/*.c ./libft/*.h
echo "\n//////// Making\n"
make re
echo "\n//////// Testing empty\n"
./fdf
echo "\n//////// Testing wrong file\n"
./fdf main.c
echo "\n//////// Testing 22 maps\n"
./fdf ./test_maps/42.fdf
./fdf ./test_maps/plat.fdf
./fdf ./test_maps/pnp_flat.fdf
./fdf ./test_maps/10-2.fdf
./fdf ./test_maps/100-6.fdf
./fdf ./test_maps/20-60.fdf
./fdf ./test_maps/50-4.fdf
./fdf ./test_maps/10-70.fdf
./fdf ./test_maps/basictest.fdf
./fdf ./test_maps/elem.fdf
./fdf ./test_maps/mars.fdf
./fdf ./test_maps/pentenegpos.fdf
./fdf ./test_maps/pylone.fdf
./fdf ./test_maps/pyra.fdf
./fdf ./test_maps/pyramide.fdf
./fdf ./maps/elem-col.fdf
./fdf ./maps/elem-fract.fdf
./fdf ./maps/elem.fdf
./fdf ./maps/elem2.fdf
./fdf ./maps/julia.fdf
./fdf ./maps/t1.fdf
./fdf ./maps/t2.fdf
echo "\n//////// Cleaning\n"
make fclean
