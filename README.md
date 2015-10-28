# FELB03
Strukture Podataka

### Veze
`src/` je lokacija svih izvornih kôdova riješenih nakon odgovarajućih tjednih vježbi.  
`src/early` su neke nestabilne/nedovršene, pak unaprijed ponekada riješene vježbe.  
`src/ideas` je ono što se treba ignorirati.  
`tests/` su neki "unit testovi" zadataka. Vjerojatno ignorirati.  
`useful/` su neke vlastite primjene. Ignorirati.  

### Instalacija
U Linuxu dovoljno je imati instaliran [GNU make](https://www.gnu.org/software/make/) i pokrenuti instalaciju s `make`.  
Nakon toga će u `bin/` biti sve izvršne datoteke za svaki pojedini zadatak iz isključivo `src/` direktorija.

Eventualno, moguće je svaku vježbu ručno compileat i pokrenit s nečim poput `gcc -Wall src/n.c -O bin/n.out && ./bin/n.out` gdje je n∈N.

### Dodatne napomene
Kôd je pisan po naputcima profesora, tako da ako je, primjerice, na satu korišten tip `void` funkcije umjesto tipa `int`, ovdje je također nastojano isto. Vrijede ista pravila za camelCase imena varijabli, CamelCase funkcija, prototipa i slično.  

Ponegdje ima vlastitih implementacija.
