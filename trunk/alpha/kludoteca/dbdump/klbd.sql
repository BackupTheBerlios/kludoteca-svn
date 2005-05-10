--
-- PostgreSQL database dump
--

SET client_encoding = 'SQL_ASCII';
SET check_function_bodies = false;

REVOKE ALL ON SCHEMA public FROM PUBLIC;

SET SESSION AUTHORIZATION 'kladmin';

-- Esquema relacional -- 

-- ldt_games(serialReference, gameName, description, rules, minGamers, maxGamers, gameType, timeUnitAdd, timeUnit, costTM, costTMA, position, state )
-- PKEY: serialReference

-- ldt_persons ( docIdent, firstName, lastName, phone, celullar, email, address);
-- PKEY: docIdent

-- ldt_clients (docIdent, incriptionDate, state, idReferencePerson )
-- PKEY: docIdent
-- FKEY: docIdent references ldt_persons(docIdent)
-- FKEY: idReferencePerson references ldt_persons(docIdent)

-- ldt_users (docIdent, login, permissions )
-- PKEY: login
-- FKEY: docIdent references ldt_persons(docIdent)

-- ldt_tournament (codTournament, gameReference, name, initDate, endDate, roundsForPair, rounds, price, discount, state)
-- PKEY: codTournament
-- FKEY: gameReference references ldt_games(serialReference)

-- ldt_participates (clientDocIdent, codTournament, nround)
-- PKEY: clientDocIdent, codTournament
-- FKEY: clientDocIdent references ldt_clients(docIdent)
-- FKEY: codTournament references ldt_tournament(codTournament)

-- ldt_rounds (codTournament, nround)
-- PKEY: nRound, codTournament
-- FKEY: codTournament references ldt_tournament(codTournament)

-- ldt_match (number, nRound, codTournament, opponent1, resultOpp1, opponent2, resultOpp2)
-- PKEY: number
-- FKEY: nRound,codTournament references ldt_rounds(nRound, codTournament)
-- FKEY: opponent1,codTournament references ldt_participates(clientDocIdent, codTournament)
-- FKEY: opponent2,codTournament references ldt_participates(clientDocIdent, codTournament)

-- 
-- ldt_enterprise(nit, address, name, phone, city)
-- PKEY: nit

-- Definicion y creacion de tablas --

drop table ldt_games cascade;
CREATE TABLE ldt_games (
	serialReference character varying(8) primary key,
	gameName character varying(50) unique NOT NULL,
	description text NOT NULL,
	rules text NOT NULL,
	minGamers int NOT NULL,
	maxGamers int NOT NULL,
	gameType character varying(10) NOT NULL,
	timeUnitAdd character varying(10) NOT NULL,
	timeUnit character varying(10) NOT NULL,
	costTM real NOT NULL,
	costTMA real NOT NULL,
	position character varying(10) NOT NULL,
	state character varying(10),
	available boolean DEFAULT 't' NOT NULL
);

insert into ldt_games values ( 'g1', 'Juego 1', 'La descripcion', 'Las reglas!', 2, 2, 'board', 'minutes', 'minutes', 1000, 1000, 'uno', 'good' ,'t' );
insert into ldt_games values ( 'g2', 'Juego 2', 'La descripcion', 'Las reglas!', 2, 2, 'board', 'minutes', 'minutes', 1000, 1000, 'uno', 'good','t' );

drop table ldt_persons cascade;
CREATE TABLE ldt_persons (
	docIdent character varying(10)  primary key,
	firstName character varying(50) NOT NULL,
	lastName character varying(50) NOT NULL,
	phone character varying(15),
	celullar character varying(15),
	email character varying(60),
	address character varying(40),
	genre character varying (10)
);

insert into ldt_persons values ( '0', 'nameadmin', 'lastadmin0', '000','000', 'krawek@gmail.com', 'busquela', 'male' );
insert into ldt_persons values ( '1', 'namecliente', 'lastcliente', '111','111', 'cliente@gmail.com', 'busquela', 'male' );
insert into ldt_persons values ( '2', 'nameuser', 'lastname', '222','222', 'user@gmail.com', 'busquela', 'male' );
insert into ldt_persons values ( '3', 'opponentadmin', 'lastopponent', '333','333', 'opponent@gmail.com', 'busquela', 'male' );
insert into ldt_persons values ( '4', 'namefamiliar', 'lastfamiliar', '444','444', 'krawek@gmail.com', 'busquela', 'male' );

drop table ldt_clients cascade;
CREATE TABLE ldt_clients (
	docIdent character varying(10) references ldt_persons(docIdent)  on delete cascade on update cascade,
	inscriptionDate date NOT NULL,
	state character varying(10),
	idReferencePerson character varying(10) references ldt_persons(docIdent),
	primary key(docIdent)
);

-- Vista para facilitar el trabajo de indexado y busqueda
create view ldt_clients_view as SELECT firstname,lastname,state from ldt_clients,ldt_persons where ldt_persons.docIdent in (select ldt_clients.docident from ldt_persons );

insert into ldt_clients values ( '1', '01-jan-05', 'activo', '4' );
insert into ldt_clients values ( '3', '01-jan-05', 'activo', '4' );

drop table ldt_users cascade;
CREATE TABLE ldt_users (
	docIdent character varying(10) references ldt_persons(docIdent) on delete cascade on update cascade,
	login character varying(20) primary key,
	permissions character varying(10) NOT NULL
);

-- Vista para facilitar el trabajo de indexado y busqueda
create view ldt_users_view as SELECT firstname,lastname,login from ldt_users,ldt_persons where ldt_persons.docident in (select ldt_users.docident from ldt_persons );

insert into ldt_users values ( '0', 'kladmin', '11111');
insert into ldt_users values ( '2', 'usuario', '11100');

drop table ldt_tournament cascade;
CREATE TABLE ldt_tournament (
	name character varying(50) primary key,
	gameReference character varying(8) references ldt_games(serialReference),
	initDate date NOT NULL,
	endDate date NOT NULL,
	roundsForPair integer NOT NULL,
	rounds integer NOT NULL,
	price real NOT NULL,
	discount real,
	active boolean DEFAULT 't'
);

-- Vista para facilitar el filtrado
create view ldt_tournament_view as select name,gamename,initdate from ldt_tournament,ldt_games where ldt_games.serialreference in ( select gamereference from ldt_games );

insert into ldt_tournament values ( 'XVI Torneo de linares', 'g1', '01-jan-05', '02-jan-05', 4, 4, 1000, 10, 't' );
insert into ldt_tournament values ( 'XVII Torneo de linares', 'g2', '01-jan-05', '02-jan-05', 4, 4, 1000, 10, 't' );
insert into ldt_tournament values ( 'XVIII Torneo de linares', 'g1', '01-jan-05', '02-jan-05', 4, 4, 1000, 10, 't' );

drop table ldt_rents;
CREATE TABLE ldt_rents (
	clientDocIdent character varying(10) NOT NULL,
	gameSerialReference character varying(10) NOT NULL,
	returnHour time without time zone NOT NULL,
	date date NOT NULL,
	foreign key (clientDocIdent) references ldt_clients(docIdent) on delete cascade on update cascade,
	foreign key (gameSerialReference) references ldt_games(serialReference) on delete cascade on update cascade
);

insert into ldt_rents values ( '1', 'g1', '12:00:00', '01-jan-05');
insert into ldt_rents values ( '3', 'g2', '12:00:00', '01-jan-05');


drop table ldt_participates cascade;
CREATE TABLE ldt_participates (
	clientDocIdent character varying(15) references ldt_clients(docIdent) on delete cascade on update cascade,
	codTournament character varying(10) references ldt_tournament(name) on delete cascade on update cascade,
	rank integer,
	primary key(clientDocIdent, codTournament)
);

drop table ldt_rounds cascade;
CREATE TABLE ldt_rounds (
	nRound integer NOT NULL,
	codTournament character varying(10) references ldt_tournament(name) on delete cascade on update cascade,
	
	primary key(nRound, codTournament)
);

drop table ldt_match;
CREATE TABLE ldt_match (
	number integer primary key,
	nRound integer,
	codTournament character varying(10),
	opponent1 character varying(10),
	resultOpp1 integer NOT NULL,
	opponent2 character varying(10),
	resultOpp2 integer NOT NULL,
	foreign key (nRound, codTournament) references ldt_rounds(nRound, codTournament) on delete cascade on update cascade,
	foreign key (opponent1,codTournament) references ldt_participates(clientDocIdent, codTournament) on delete cascade on update cascade,
	foreign key (opponent2,codTournament) references ldt_participates(clientDocIdent, codTournament) on delete cascade on update cascade
);
	

drop table ldt_enterprise;
CREATE TABLE ldt_enterprise (
	nit character varying(10) NOT NULL,
	address character varying(40) NOT NULL,
	name character varying(50) NOT NULL,
	phone character varying(10) NOT NULL,
	city character varying(15) NOT NULL,
	primary key(nit)
);






