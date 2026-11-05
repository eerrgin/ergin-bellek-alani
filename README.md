# ergin-bellek-alani

Ergin Kaplan, Istanbul. Kisisel calisma. Ucuncu taraf urun adi veya sirket yok.

## Hangi gercek problem

Gece boyunca acik kalan yerel bir gunluk toplayicisi, her satir icin `malloc` cagirirsa kucuk parcalar birikir. Bu depo, o is icin sabit kapasiteli bir bellek alani kullanir. Tur bitince `arena_reset` isaretciyi basa alir; bloklar isletim sistemine tek tek iade edilmez, cunku zaten tek parca ayrilmistir.

## Ne kanitlar

- Hizali isaretci aritmetigi (`align` ikinin kuvveti degilse ayirma reddedilir).
- Tasma: istek kapasiteyi asarsa `NULL`, onceki kullanim bozulmaz.
- Sahiplik: alan yok edilince tek `free`. Cift serbest birakma yok; kullanicidan gelen isaretci `free` edilmez.
- Sifirlama sonrasi ayni adres yeniden verilebilir. Bu, omur sozlesmesidir: reset'ten sonra eski isaretci gecersizdir.

## Calistirma

```bash
make test
```

Testler GitHub Actions uzerinde `ubuntu-latest` ile de kosar.
