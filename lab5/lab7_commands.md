gcc -o dynamic_loader dynamic_loader.c -ldl
./dynamic_loader

cat /proc/1450267/maps
- 1450267 - ID процесса, к-ый создает программа

cat /proc/1490359/maps
5ab7c94b3000-5ab7c94b4000 r--p 00000000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
5ab7c94b4000-5ab7c94b5000 r-xp 00001000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
5ab7c94b5000-5ab7c94b6000 r--p 00002000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
5ab7c94b6000-5ab7c94b7000 r--p 00002000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
5ab7c94b7000-5ab7c94b8000 rw-p 00003000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
5ab7cddd7000-5ab7cddf8000 rw-p 00000000 00:00 0                          [heap]
72c4f3a00000-72c4f3a28000 r--p 00000000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
72c4f3a28000-72c4f3bb0000 r-xp 00028000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
72c4f3bb0000-72c4f3bff000 r--p 001b0000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
72c4f3bff000-72c4f3c03000 r--p 001fe000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
72c4f3c03000-72c4f3c05000 rw-p 00202000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
72c4f3c05000-72c4f3c12000 rw-p 00000000 00:00 0 
72c4f3dba000-72c4f3dbd000 rw-p 00000000 00:00 0 
72c4f3dc6000-72c4f3dc8000 rw-p 00000000 00:00 0 
72c4f3dc8000-72c4f3dc9000 r--p 00000000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
72c4f3dc9000-72c4f3df4000 r-xp 00001000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
72c4f3df4000-72c4f3dfe000 r--p 0002c000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
72c4f3dfe000-72c4f3e00000 r--p 00036000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
72c4f3e00000-72c4f3e02000 rw-p 00038000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7ffed0f49000-7ffed0f6b000 rw-p 00000000 00:00 0                          [stack]
7ffed0fc4000-7ffed0fc8000 r--p 00000000 00:00 0                          [vvar]
7ffed0fc8000-7ffed0fca000 r-xp 00000000 00:00 0                          [vdso]
cat /proc/1562424/maps
575a98a84000-575a98a85000 r--p 00000000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a85000-575a98a86000 r-xp 00001000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a86000-575a98a87000 r--p 00002000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a87000-575a98a88000 r--p 00002000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a88000-575a98a89000 rw-p 00003000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575ac3fa1000-575ac3fc2000 rw-p 00000000 00:00 0                          [heap]
748def000000-748def028000 r--p 00000000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def028000-748def1b0000 r-xp 00028000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def1b0000-748def1ff000 r--p 001b0000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def1ff000-748def203000 r--p 001fe000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def203000-748def205000 rw-p 00202000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def205000-748def212000 rw-p 00000000 00:00 0 
748def385000-748def388000 rw-p 00000000 00:00 0 
748def391000-748def393000 rw-p 00000000 00:00 0 
748def393000-748def394000 r--p 00000000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def394000-748def3bf000 r-xp 00001000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def3bf000-748def3c9000 r--p 0002c000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def3c9000-748def3cb000 r--p 00036000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def3cb000-748def3cd000 rw-p 00038000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7fff4a2fd000-7fff4a31f000 rw-p 00000000 00:00 0                          [stack]
7fff4a327000-7fff4a32b000 r--p 00000000 00:00 0                          [vvar]
7fff4a32b000-7fff4a32d000 r-xp 00000000 00:00 0                          [vdso]
cat /proc/1562424/maps
575a98a84000-575a98a85000 r--p 00000000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a85000-575a98a86000 r-xp 00001000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a86000-575a98a87000 r--p 00002000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a87000-575a98a88000 r--p 00002000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a88000-575a98a89000 rw-p 00003000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575ac3fa1000-575ac3fc2000 rw-p 00000000 00:00 0                          [heap]
748def000000-748def028000 r--p 00000000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def028000-748def1b0000 r-xp 00028000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def1b0000-748def1ff000 r--p 001b0000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def1ff000-748def203000 r--p 001fe000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def203000-748def205000 rw-p 00202000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def205000-748def212000 rw-p 00000000 00:00 0 
748def385000-748def388000 rw-p 00000000 00:00 0 
748def38c000-748def38d000 r--p 00000000 08:50 151710                     /home/christmas_fire/os/lab5/liblist.so
748def38d000-748def38e000 r-xp 00001000 08:50 151710                     /home/christmas_fire/os/lab5/liblist.so
748def38e000-748def38f000 r--p 00002000 08:50 151710                     /home/christmas_fire/os/lab5/liblist.so
748def38f000-748def390000 r--p 00002000 08:50 151710                     /home/christmas_fire/os/lab5/liblist.so
748def390000-748def391000 rw-p 00003000 08:50 151710                     /home/christmas_fire/os/lab5/liblist.so
748def391000-748def393000 rw-p 00000000 00:00 0 
748def393000-748def394000 r--p 00000000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def394000-748def3bf000 r-xp 00001000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def3bf000-748def3c9000 r--p 0002c000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def3c9000-748def3cb000 r--p 00036000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def3cb000-748def3cd000 rw-p 00038000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7fff4a2fd000-7fff4a31f000 rw-p 00000000 00:00 0                          [stack]
7fff4a327000-7fff4a32b000 r--p 00000000 00:00 0                          [vvar]
7fff4a32b000-7fff4a32d000 r-xp 00000000 00:00 0                          [vdso]
cat /proc/1562424/maps
575a98a84000-575a98a85000 r--p 00000000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a85000-575a98a86000 r-xp 00001000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a86000-575a98a87000 r--p 00002000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a87000-575a98a88000 r--p 00002000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a88000-575a98a89000 rw-p 00003000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575ac3fa1000-575ac3fc2000 rw-p 00000000 00:00 0                          [heap]
748def000000-748def028000 r--p 00000000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def028000-748def1b0000 r-xp 00028000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def1b0000-748def1ff000 r--p 001b0000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def1ff000-748def203000 r--p 001fe000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def203000-748def205000 rw-p 00202000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def205000-748def212000 rw-p 00000000 00:00 0 
748def385000-748def388000 rw-p 00000000 00:00 0 
748def38c000-748def38d000 r--p 00000000 08:50 151710                     /home/christmas_fire/os/lab5/liblist.so
748def38d000-748def38e000 r-xp 00001000 08:50 151710                     /home/christmas_fire/os/lab5/liblist.so
748def38e000-748def38f000 r--p 00002000 08:50 151710                     /home/christmas_fire/os/lab5/liblist.so
748def38f000-748def390000 r--p 00002000 08:50 151710                     /home/christmas_fire/os/lab5/liblist.so
748def390000-748def391000 rw-p 00003000 08:50 151710                     /home/christmas_fire/os/lab5/liblist.so
748def391000-748def393000 rw-p 00000000 00:00 0 
748def393000-748def394000 r--p 00000000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def394000-748def3bf000 r-xp 00001000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def3bf000-748def3c9000 r--p 0002c000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def3c9000-748def3cb000 r--p 00036000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def3cb000-748def3cd000 rw-p 00038000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7fff4a2fd000-7fff4a31f000 rw-p 00000000 00:00 0                          [stack]
7fff4a327000-7fff4a32b000 r--p 00000000 00:00 0                          [vvar]
7fff4a32b000-7fff4a32d000 r-xp 00000000 00:00 0                          [vdso]
cat /proc/1562424/maps
575a98a84000-575a98a85000 r--p 00000000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a85000-575a98a86000 r-xp 00001000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a86000-575a98a87000 r--p 00002000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a87000-575a98a88000 r--p 00002000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575a98a88000-575a98a89000 rw-p 00003000 08:50 162090                     /home/christmas_fire/os/lab5/dynamic_loader
575ac3fa1000-575ac3fc2000 rw-p 00000000 00:00 0                          [heap]
748def000000-748def028000 r--p 00000000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def028000-748def1b0000 r-xp 00028000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def1b0000-748def1ff000 r--p 001b0000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def1ff000-748def203000 r--p 001fe000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def203000-748def205000 rw-p 00202000 08:50 49756                      /usr/lib/x86_64-linux-gnu/libc.so.6
748def205000-748def212000 rw-p 00000000 00:00 0 
748def385000-748def388000 rw-p 00000000 00:00 0 
748def391000-748def393000 rw-p 00000000 00:00 0 
748def393000-748def394000 r--p 00000000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def394000-748def3bf000 r-xp 00001000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def3bf000-748def3c9000 r--p 0002c000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def3c9000-748def3cb000 r--p 00036000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
748def3cb000-748def3cd000 rw-p 00038000 08:50 49753                      /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7fff4a2fd000-7fff4a31f000 rw-p 00000000 00:00 0                          [stack]
7fff4a327000-7fff4a32b000 r--p 00000000 00:00 0                          [vvar]
7fff4a32b000-7fff4a32d000 r-xp 00000000 00:00 0                          [vdso]
cat /proc/1562424/maps
cat: /proc/1562424/maps: No such file or directory