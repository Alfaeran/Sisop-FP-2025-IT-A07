# Final Project Sistem Operasi IT

## Peraturan

1. Waktu pengerjaan dimulai hari Kamis (19 Juni 2025) setelah soal dibagikan hingga hari Rabu (25 Juni 2025) pukul 23.59 WIB.
2. Praktikan diharapkan membuat laporan penjelasan dan penyelesaian soal dalam bentuk Readme(github).
3. Format nama repository github “Sisop-FP-2025-IT-[Kelas][Kelompok]” (contoh:Sisop-FP-2025-IT-A01).
4. Setelah pengerjaan selesai, seluruh source code dan semua script bash, awk, dan file yang berisi cron job ditaruh di github masing - masing kelompok, dan link github dikumpulkan pada form yang disediakan. Pastikan github di setting ke publik.
5. Commit terakhir maksimal 10 menit setelah waktu pengerjaan berakhir. Jika melewati maka akan dinilai berdasarkan commit terakhir.
6. Jika tidak ada pengumuman perubahan soal oleh asisten, maka soal dianggap dapat diselesaikan.
7. Jika ditemukan soal yang tidak dapat diselesaikan, harap menuliskannya pada Readme beserta permasalahan yang ditemukan.
8. Praktikan tidak diperbolehkan menanyakan jawaban dari soal yang diberikan kepada asisten maupun praktikan dari kelompok lainnya.
9. Jika ditemukan indikasi kecurangan dalam bentuk apapun di pengerjaan soal final project, maka nilai dianggap 0.
10. Pengerjaan soal final project sesuai dengan modul yang telah diajarkan.

## Kelompok A19

Nama | NRP
--- | ---
Kanafira Vanesha Putri | 5027241010
Angga Firmansyah | 5027241062
Tiara Fatimah Azzahra | 5027241090
M. Alfaeran Auriga Ruswandi | 5027241115  

Implementasi terdiri dari dua program utama:

1. **Server Program (server.c)**:
   - Membuat named pipe menggunakan `mkfifo()`
   - Menunggu koneksi dari client
   - Menerima pesan dari client dan memberikan response
   - Mencatat semua komunikasi ke `history.log`
   - Cleanup otomatis saat program berakhir

2. **Client Program (client.c)**:
   - Terhubung ke named pipe yang sudah dibuat server
   - Mengirim pesan ke server dan menerima response
   - Mencatat semua komunikasi ke `history.log`
   - Dapat mengakhiri komunikasi dengan perintah "exit"

3. **Build dan Run Scripts**:
   - `build.sh`: Kompilasi kedua program
   - `run_server.sh`: Menjalankan server
   - `run_client.sh`: Menjalankan client

### 2. Logging System

**Teori**

Logging adalah proses pencatatan aktivitas dan events yang terjadi dalam sistem. Dalam konteks komunikasi antar proses, logging membantu untuk:

- Debugging dan troubleshooting
- Audit trail komunikasi
- Monitoring sistem
- Analisis performa

**Solusi**

Sistem logging yang diimplementasikan:

- Setiap pesan yang dikirim dan diterima dicatat
- Format log: `[ROLE-ACTION] message`
- File log: `history.log`
- No timestamp sesuai permintaan soal

Format logging:

```
[CLIENT-SENT] Hello Server
[SERVER-RECEIVED] Hello Server
[SERVER-SENT] Hello Client
[CLIENT-RECEIVED] Hello Client
```

### 3. Error Handling dan Cleanup

**Teori**

Proper error handling dan cleanup sangat penting dalam system programming untuk:

- Mencegah resource leaks
- Memastikan konsistensi sistem
- Graceful program termination
- Recovery dari error conditions

**Solusi**

- Signal handlers untuk SIGINT dan SIGTERM
- Automatic cleanup named pipe saat program berakhir
- Error checking untuk semua system calls
- Proper file descriptor management
- Graceful shutdown sequence

**Video Menjalankan Program**

Untuk menjalankan program:

1. Kompilasi: `./scripts/build.sh` atau `make all`
2. Terminal 1: `./scripts/run_server.sh`
3. Terminal 2: `./scripts/run_client.sh`
4. Mulai komunikasi
5. Ketik "exit" di client untuk keluar

Alternatif testing:

- `make demo` - Demo otomatis
- `make test` - Testing komprehensif
- `./scripts/test.sh` - Manual testing

**Contoh Output History Log:**

```log
[CLIENT] Connected to server
[CLIENT-SENT] Hello Server!
[SERVER-RECEIVED] Hello Server!
[SERVER-SENT] Hello Client! Nice to meet you
[CLIENT-RECEIVED] Hello Client! Nice to meet you
[CLIENT-SENT] exit
[CLIENT] Exiting
[SERVER] Client requested exit
```

## Daftar Pustaka

1. Stevens, W. Richard, and Stephen A. Rago. "Advanced Programming in the UNIX Environment." 3rd Edition. Addison-Wesley Professional, 2013.
2. Love, Robert. "Linux System Programming: Talking Directly to the Kernel and C Library." 2nd Edition. O'Reilly Media, 2013.
3. Kerrisk, Michael. "The Linux Programming Interface: A Linux and UNIX System Programming Handbook." No Starch Press, 2010.
