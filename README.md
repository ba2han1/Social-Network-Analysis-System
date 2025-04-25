# Sosyal Ağ Tabanlı Kullanıcı Yönetim ve Analiz Sistemi

Bu C programı, Red-Black Tree veri yapısı kullanarak kullanıcıları yönetir ve sosyal ağ üzerinde arkadaşlık ilişkileri, etki alanı, topluluk tespiti gibi analizleri yapar. Ek olarak oluşturulan veriler `.txt` dosyasına kaydedilir.

## Özellikler

- Red-Black Tree ile kullanıcı ekleme ve arama
- Arkadaşlık ilişkileri tanımlama
- DFS ile derinlik tabanlı dolaşım
- Ortak arkadaş analizi
- Etki alanı (influence area) hesaplama
- Topluluk tespiti
- Verileri dosyaya kaydetme ve gösterme

---

## 1. Kullanıcı ve Arkadaşlık Tanımı

Kullanıcı sayısı ve her bir kullanıcı için ID bilgisi alındıktan sonra, arkadaşlık ilişkileri tanımlanır.

📸 **Ekran Görüntüsü (Kullanıcı ve Arkadaşlık Girişi)**  

![Ekran görüntüsü 2025-04-25 153650](https://github.com/user-attachments/assets/a3e7d1c2-5fa2-4677-80cc-15d15864c7da)

![Ekran görüntüsü 2025-04-25 153731](https://github.com/user-attachments/assets/2aae7907-d9b9-42e9-a581-2072d70aa263)

---

## 2. DFS ile Derinlik Bazlı Gezinme

Bir kullanıcıdan başlanarak 2 derinliğe kadar olan arkadaşları ekrana yazdırılır.

📸 **Ekran Görüntüsü (DFS Çıktısı)**  

![Ekran görüntüsü 2025-04-25 153738](https://github.com/user-attachments/assets/6f9e07ee-097f-4a87-b5f9-b22786539fa2)


---

## 3. Ortak Arkadaş Analizi

İki kullanıcı arasında ortak arkadaşlar ekrana yazdırılır.

📸 **Ekran Görüntüsü (Ortak Arkadaş Çıktısı)**  


![Ekran görüntüsü 2025-04-25 153750](https://github.com/user-attachments/assets/66509ab2-b95a-4a47-8490-020249d3fea3)

---

## 4. Etki Alanı Hesaplama

Belirli bir kullanıcıdan başlayarak etki alanındaki tüm kullanıcılar ve toplam sayıları hesaplanır.

📸 **Ekran Görüntüsü (Etki Alanı Çıktısı)**  

![Ekran görüntüsü 2025-04-25 153755](https://github.com/user-attachments/assets/106cf1c0-4de1-42a7-9f14-9a4f11d57391)


## 5. Topluluk Tespiti

Program, tüm kullanıcılar üzerinde gezerek bağlı toplulukları belirler.

📸 **Ekran Görüntüsü (Topluluk Çıktısı)**  

(topluluk değeri 2. değer olarak alınmalıdır)
![Ekran görüntüsü 2025-04-25 153802](https://github.com/user-attachments/assets/aa6f6541-ae13-47c6-8f8d-036b4d35cbc7)

---

## 6. Dosyaya Yazma

`veriseti.txt` dosyasına kullanıcılar ve arkadaşlık ilişkileri yazılır.

📸 **Ekran Görüntüsü (veriseti.txt İçeriği)**  
*cmd ekranın çıktısı:
![Ekran görüntüsü 2025-04-25 153815](https://github.com/user-attachments/assets/51b14afa-4493-46e2-a4f5-1e6753d7ea72)

*veriseti.txt dosyasının içi:

![Ekran görüntüsü 2025-04-25 153846](https://github.com/user-attachments/assets/0ea8dabc-4c3e-40b5-9eba-c5e3fb45ce6a)

---

## Derleme ve Çalıştırma

```bash
gcc program.c -o program
./program
Notlar
Program maksimum 100 kullanıcı desteklemektedir.

Red-Black Tree ile arama ve ekleme işlemleri O(log n) karmaşıklıktadır.

Veriler veriseti.txt dosyasına yazılır ve program sonunda bu dosyanın içeriği görüntülenir.

Lisans
Bu proje herhangi bir lisans altında değildir. Dilerseniz kaynak kodları kullanabilir ve değiştirebilirsiniz.
