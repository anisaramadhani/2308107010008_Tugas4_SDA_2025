# 2308107010008_Tugas4_SDA_2025
Nama   : Anisa Ramadhani
NPM    : 2308107010008

# Deskripsi Tugas
Tugas ini bertujuan untuk menguji performa berbagai algoritma sorting pada dataset yang berisi angka dan string dalam jumlah besar. Program ditulis dalam bahasa C dan memanfaatkan beberapa algoritma sorting klasik untuk membandingkan kecepatan eksekusi dan penggunaan memori.

# Eksperimen
- Pengujian dilakukan dengan jumlah data: **10.000**, **50.000**, **100.000**, **250.000**, **500.000**, **1.000.000**, **1.500.000**, dan **2.000.000**.
- Hasil eksperimen disajikan dalam bentuk tabel dan grafik perbandingan waktu dan memori di dalam laporan PDF.

# Fitur Program
- Memuat data angka dari file `data_angka.txt`
- Memuat data string dari file `data_kata.txt`
- Melakukan sorting data angka menggunakan:
  - Bubble Sort
  - Selection Sort
  - Insertion Sort
  - Merge Sort
  - Quick Sort
  - Shell Sort
- Melakukan sorting data string menggunakan:
  - Bubble Sort
  - Selection Sort
  - Insertion Sort
  - Merge Sort (menggunakan `qsort`)
  - Quick Sort (menggunakan `qsort`)
  - Shell Sort
- Melakukan benchmarking waktu eksekusi dan penggunaan memori untuk setiap algoritma
- Menampilkan hasil benchmarking dalam format tabel yang rapi di terminal
