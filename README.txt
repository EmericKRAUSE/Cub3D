bug:
Pas de bug lors des deplacements dans les coins

Par contre des soucis lors de l'utilisation de la map debug:
(column_height demesurement grand)

(lldb) 
Process 2503210 stopped
* thread #1, name = 'Cub3D', stop reason = step over
    frame #0: 0x00005555555585b3 Cub3D`draw_slice(game=0x00005555555982a0, i=1561, ray_angle=<unavailable>, slice=<unavailable>) at draw_slice.c:47:8
   44           start_y = (WIN_HEIGHT / 2) - (column_height / 2);
   45           texture.x = slice.hit_ratio * slice.texture->width;
   46           y = start_y;
-> 47           while (y < WIN_HEIGHT / 2 + column_height / 2)
   48           {
   49                   texture.y = ((y - start_y) * slice.texture->height) / column_height;
   50                   if (y >= 0 && y < WIN_HEIGHT)
(lldb) p y
(int) $0 = 10418195
(lldb) p column_height 
(int) $1 = 88617614
(lldb) bt
* thread #1, name = 'Cub3D', stop reason = step over
  * frame #0: 0x00005555555585b3 Cub3D`draw_slice(game=0x00005555555982a0, i=1561, ray_angle=<unavailable>, slice=<unavailable>) at draw_slice.c:47:8
    frame #1: 0x0000555555558c00 Cub3D`ray_casting at ray_casting.c:82:3
    frame #2: 0x0000555555558be9 Cub3D`ray_casting(game=0x00005555555982a0) at ray_casting.c:105:3
    frame #3: 0x000055555555dfd6 Cub3D`mlx_loop + 310
    frame #4: 0x0000555555557610 Cub3D`main(argc=2, argv=0x00007fffffffdca8) at main.c:179:2
    frame #5: 0x00007ffff7c29d90 libc.so.6`__libc_start_call_main(main=(Cub3D`main at main.c:142:1), argc=2, argv=0x00007fffffffdca8) at libc_start_call_main.h:58:16
    frame #6: 0x00007ffff7c29e40 libc.so.6`__libc_start_main_impl(main=(Cub3D`main at main.c:142:1), argc=2, argv=0x00007fffffffdca8, init=<unavailable>, fini=<unavailable>, rtld_fini=<unavailable>, stack_end=0x00007fffffffdc98) at libc-start.c:392:3
    frame #7: 0x0000555555557675 Cub3D`_start + 37


Note : fonction cree: permet d'encercler la map avec le caractere de son choix
