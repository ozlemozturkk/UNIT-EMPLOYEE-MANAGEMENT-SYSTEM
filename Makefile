# ******************************************************************************
# Makefile - Proje1
# Bu makefile, "main.c" ve "Proje1.c" dosyalarını derlerim ve "Proje1.exe" 
# adlı çalıştırılabilir dosyayı oluştururum.
# Birim ve çalışan bilgilerini "birimler.txt" ve "calisanlar.txt" dosyalarından
# alarak çalıştırırım.
#
# @assignment 1. ödev
# @date 10.12.2024 - 23.12.2024
# @author
# Özlem Öztürk, ozlem.ozturk@stu.fsm.edu.tr
# ******************************************************************************

# Derleyici ve derleme seçeneklerini burada tanımlarım.
CC=gcc
CFLAGS=-c -Wall

# "all" ile tüm işlemleri yaparım: derlerim ve çalıştırırım.
all: Proje1 run

# "Proje1" ile obje dosyalarını birleştirip çalıştırılabilir dosyayı oluştururum.
Proje1: main.o Proje1.o
	$(CC) main.o Proje1.o -o Proje1

# "main.o" ile "main.c" dosyasını derlerim ve obje dosyasını üretirim.
main.o: main.c
	$(CC) $(CFLAGS) main.c

# "Proje1.o" ile "Proje1.c" dosyasını derlerim ve obje dosyasını üretirim.
Proje1.o: Proje1.c Proje1.h
	$(CC) $(CFLAGS) Proje1.c
	
# "clean" ile gereksiz dosyaları temizlerim.
clean:
	del *.o Proje1.exe

# "run" ile oluşturduğum çalıştırılabilir dosyayı argümanlarla çalıştırırım.
run:
	Proje1.exe birimler.txt calisanlar.txt

