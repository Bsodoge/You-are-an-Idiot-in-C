# You-are-an-Idiot-in-C
You are an Idiot! recreated in C using GTK

Build with
```bash
gcc $(pkg-config --cflags gtk+-2.0) $(pkg-config --cflags libvlc) -c main.c -o gtktest
gcc gtktest -o test $(pkg-config --libs libvlc) $(pkg-config --cflags gtk+-2.0)
```

TODO: Add example gif