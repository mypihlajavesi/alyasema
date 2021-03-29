# Älyasema

Liikkuva kylä -hanke on vuosien 2020 - 2021 aikana Keuruun Pihlajavedellä toteutettu Leader -rahoituksella käynnistetty kehityshanke, johon Leader Vesuri-ryhmä on myöntänyt rahoitusta EU:n maaseuturahastosta. Hankkeen yhteydessä perustettiin Älyasema -tutkimusasema, jonka yhteyteen rakennettiin ympäröivää luontoa havainnoiva mittauslaitteisto.

Mittauslaitteisto rakennettiin Arduino MKR WAN 1310 -mikrokontrollereita ja niiden käyttämää LoRa -modulaatiotekniikkaa hyväksikäyttäen. Tältä sivulta löydät Älyaseman mittauslaitteiston lähdekoodit, joiden avulla vastaavan mittauslaitteiston rakentaminen jonnekin muualle on mahdollista.

# Asennus ja koodin käyttöönotto

1. Koodi käyttää kustomoitua WAA_Arduino_MKRENV.h -kirjastoa. Lataa kirjasto lib -hakemistosta ja asenna se Arduino IDE:n (Sketch > Include Library > Add .ZIP Library)

2. Muodosta tili Arduino Iot Cloud -palveluun

3. Luo Arduino Thing ja lisää thingProperties.h -tiedostossa eritellyt muuttujat. Huom! Sinun tarvitsee lisätä muuttujat juuri samassa järjestyksessä kuin ne on listattu thingProperties.h -tiedostossa. Muuttujia luodessa ne saavat järjestysnumeron / ID-arvon Arduino Iot Cloud -palvelussa. Ko. ID on sama kuin thingProperties.h -tiedostossa muuttujanimen jälkeen ilmoitettu arvo.

4. Lisää sinun oma THING_ID arduino_secrets.h tiedostoon. Arvon löydät Arduino Iot Cloud -palvelusta.

5. Lisää sinun oma SECRET_APP_EUI ja SECRET_APP_KEY thingProperties.h tiedostoon. Arvot löydät Arduino Iot Cloud -palvelusta.

6. Sensori mittaa ilmanpainetta, jonka suuruuten vaikuttaa mittauspaikan korkeus merenpinnasta mitattuna. Päivitä oman mittauspaikkasi korkeus metreinä ArduinoMKRWAN1310-WeatherProject.ino -tiedostoon asettamalla se altitude -muuttujan arvoksi.

7. Siirrä muokkaamasi src -hakemiston tiedostot omaan Arduino MKR WAN 1310 -laitteeseesi

# Yhteydenotot

Koodia koskevia kysymyksiä voi lähettää osoitteeseen info [at] mypihlajavesi.fi.

# Tausta

Älyaseman mittauslaitteiston toteutus pohjautuu Andreas Waldherrin Arduino -projektiin 'MKR WAN 1310 IoT - operating at 0, 92mA'. Koodia on yksinkertaistettu poistamalla Andreaksen kehittämä 'Serial Service Menue', joka on komentotulkin kautta käytettävä ohjauspaneeli mikrokontrollerin hallintaan. Mikäli haluat hyödyntää alkuperäistä koodia, löytyy se Arduinon Project hubista, osoitteesta: https://create.arduino.cc/projecthub/andreas_waldherr/mkr-wan-1310-iot-operating-at-0-92ma-879793.
