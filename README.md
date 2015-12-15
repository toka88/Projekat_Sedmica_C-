# Projekat_Sedmica_C-

Aplikacija ima korisnike i sifre.
Server je na ploci, klijent na vm.
Na serveru se pamte korisnici i sifre u txt fajlu.
Korisnici se preko etherneta kace na server.
Server kada se loguju dva korisnika zapocinje partiju.
Za korisnike se pamti usename, sifra i broj rejting poena.
Na displeju se ispisuje svaki primljen i poslat ethernet paket.
Pritiskom na displej, ceo sadrzaj se brise.
Kada se dodje do kraja displeja sa porukama, on pocinje da se
skroluje.
Server aplikacija treba da omoguci da se igra vise partija
istovremeno.
Preko serijske komunikacije se dobija admin pristu serveru.
Preko admin pristupa korisnici mogu da se blokiraju.
Kada se prvi put korisnik looguje, odredjuje mu se user i sifra.
Pocetni rejting je 1000.
Za pobedu se dobija 10, za poraz -10 poena.
