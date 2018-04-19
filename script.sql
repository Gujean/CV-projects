create table organizatori
(id_org number(3) constraint PK1 primary key,
nume varchar2(25) not null,
data_nasterii date not null,
telefon char(10) not null);


create table personal
(id_personal number(3) constraint PK2 primary key,
nume varchar2(25) not null,
ocupatie varchar2(20) not null,
id_org number(3) not null,
constraint fk_organizatori foreign key(id_org) references organizatori(id_org));


create table inscrieri
(data date constraint PK3 primary key,
id_personal number(3) not null,
id_participant number(3) not null,
constraint fk_personal foreign key(id_personal) references personal(id_personal),
constraint fk_participant foreign key(id_participant) references participanti(id_participant));


create table locatii
(id_locatie number(3) constraint pk_locatie primary key,
nume varchar2(25) not null);


create table punctaje
(val number(2) constraint pk_punctaj primary key);


create table premii
(id_premiu number(3) constraint pk_premiu primary key,
nume varchar2(25) not null,
val number(2) not null,
constraint fk_punctaj foreign key(val) references punctaje(val));


create table obiecte
(id_obiect number(3) constraint pk_obiecte primary key,
nume varchar2(25) not null,
tip varchar2(20) not null,
id_locatie number(3) not null,
val number(2) not null,
constraint fk_locatie foreign key(id_locatie) references locatii(id_locatie),
constraint fk_punctaje foreign key(val) references punctaje(val));

create table trasee
(id_traseu number(3) constraint pk_traseu primary key,
nume varchar2(25) not null,
lungime number(4) not null,
id_locatie number(3) not null,
constraint fk_loc foreign key(id_locatie) references locatii(id_locatie));

create table echipe 
(id_echipa number(3) constraint pk_echipa primary key,
nume varchar2(25) not null,
id_traseu number(3) not null,
constraint fk_traseu foreign key(id_traseu) references trasee(id_traseu));

create table participanti
(id_participant number(3) constraint pk_participant primary key,
nume varchar2(25) not null,
data_nasterii date not null,
telefon char(10) not null,
email varchar2(35) not null,
id_echipa number(3) not null,
constraint fk_echipa foreign key(id_echipa) references echipe(id_echipa));



insert into organizatori VALUES
(1,'Robert Nastase','06/01/1989','0781424195'),
(2,'Grigore Mihai','07/02/1999','0789424595'),
(3,'Jitca David','05/015/1979','0789628595'),
(4,'Crisan Marius','07/16/1997','0769626594'),
(5,'Razvan Mitre','08/14/1987','0768626594');

insert into locatii VALUES
(30,'Muntele Everest'),
(31,'Munti Retezat'),
(32,'Amazon'),
(33,'Valea Loarei'),
(34,'Colorado');

insert into trasee VALUES
(25,'sud-est Nepal',8000,30),
(26,'Ghetarul Scarisoara',20,31),
(27,'bra?ul Para',6500,32),
(28,'Le Chateau Royal',600,33),
(29,'Marele Canion',450,34);

insert into echipe VALUES
(20,'The Seekers',25),
(21,'Boomerang runners',26),
(22,'Water finders',27),
(23,'The white walkers',28),
(24,'Path chasers',29);

insert into participanti VALUES
(40,'Cain Motas','04/05/1997','0673823572','casindasd@yahoo.com',20),
(41,'Big Shaq','05/06/1997','0673883572','mansnothot@yahoo.com',20),
(42,'Big Khaled','06/07/1998','0673883642','khaleddj@yahoo.com',21),
(43,'Junior maywheather','07/12/1978','0673683641','boxingchamp@yahoo.com',21),
(44,'Conor McNuggets','07/17/1982','0673683632','mmachamp@yahoo.com',22),
(45,'Shawn Omalley','07/17/1982','0673683392','safas@yahoo.com',22),
(46,'Dilan brien','07/17/1982','0673684492','bossman@yahoo.com',23),
(47,'Ricky Martin','07/17/1992','0675684492','bonne8@yahoo.com',23),
(48,'Tony Ferguson','08/27/1972','0675692292','bomberman@yahoo.com',24),
(49,'Jack presley','09/27/1972','0675691292','jackie23@yahoo.com',24),

insert into personal VALUES
(6,'Cristescu Dumitru','cameraman',3),
(7,'Bulardra Stefania','electrician',2),
(8,'Marin Dragos','Operator lumini',1),
(9,'Ganea Alin','Operator intrari',4),
(10,'Sima George','Gardian',5),
(11,'Hulea Ion','Inscrieri',4),
(12,'Portase Maria','Inscrieri',2);

insert into inscrieri VALUES
('03/05/2017',11,40),
('04/05/2017',11,41),
('04/06/2017',12,42),
('05/06/2017',11,43),
('05/07/2017',12,44),
('07/07/2017',12,45),
('07/17/2017',12,46),
('07/11/2017',11,47),
('08/10/2017',11,48),
('08/18/2017',11,49);

insert into punctaje VALUES
(80),
(85),
(90),
(93),
(99);

insert into obiecte values
(50,'tricou messi','greu',31,90),
(51,'glob de cristal','mediu',33,85),
(52,'cort','usor',30,80),
(53,'barca','greu',32,93),
(54,'fantana','greu',34,99);

insert into premii values
(55,'10.000$',99),
(56,'3.000$',93),
(57,'1.000$',90),
(58,'Ps4',85),
(59,'Televizor',80);

ALTER TABLE participanti ADD CNP VARCHAR(40);

ALTER TABLE participanti DROP column CNP ;

update locatii set nume='Himalaya'
where id_locatie=30;


update trasee set nume='micut'
where lungime <=6000;

update premii
set nume='1.000$'
where val >=93;

select * from organizatori;

select nume,telefon from participanti order by nume;

select nume from obiecte
where val <  ( select avg(val) from obiecte);

select p.nume,s.nume
from echipe s,participanti p
where p.id_echipa=s.id_echipa;

select  count(id_echipa)
from participanti
group by id_echipa;

select count(id_personal)
from inscrieri
where id_personal=12;

select  s.nume,p.nume
from trasee s,locatii p
where s.id_locatie=p.id_locatie;

select  nume,ocupatie 
from personal
where ocupatie != 'Inscrieri;

select nume,  val 
from premii;

ALTER TABLE participanti ADD  nickname VARCHAR(40);

ALTER TABLE participanti drop column nickname ;

ALTER TABLE participanti modify  nume varchar2(40) ;

update premii
set nume='ps4'
where val >=90;


update trasee set nume='mare'
where lungime >6000;

select * from obiecte
where id_obiect<52;


Select  * from organizatori 
Order by data_nasterii;

Select  nume from locatii;

Select  nume,data_nasterii from participanti
Order by data_nasterii;

select  nume ,lungime from trasee
where  nume='mare';








