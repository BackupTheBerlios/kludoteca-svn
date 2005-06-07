-- KLudoteca

SET client_encoding = 'SQL_ASCII';
SET check_function_bodies = false;

REVOKE ALL ON SCHEMA public FROM PUBLIC;

SET SESSION AUTHORIZATION 'kladmin';

drop trigger ldt_addTournamentTrigger on ldt_tournament;
drop trigger ldt_rentGameTrigger on ldt_rents;
drop function ldt_updateGameAvail() cascade;

drop view ldt_users_view cascade;
drop view ldt_clients_view cascade;
drop view ldt_tournament_view cascade;

drop table ldt_users cascade;
drop table ldt_participates cascade;
drop table ldt_rents cascade;
drop table ldt_tournament cascade;
drop table ldt_clients cascade;
drop table ldt_games cascade;
drop table ldt_rounds cascade;
drop table ldt_match cascade;
drop table ldt_enterprise cascade;
drop table ldt_persons cascade;

drop domain ldt_genre_domain;
drop domain ldt_points_domain;
drop domain ldt_timeunit_domain;


CREATE FUNCTION plpgsql_call_handler() RETURNS language_handler AS '$libdir/plpgsql' LANGUAGE C;
CREATE TRUSTED PROCEDURAL LANGUAGE plpgsql HANDLER plpgsql_call_handler;
CREATE DOMAIN ldt_genre_domain as char(1) check(value in ('f', 'm'));
CREATE DOMAIN ldt_points_domain as smallint check (value in ('0','1','3'));
CREATE DOMAIN ldt_timeunit_domain as char(1) check(value in ('m', 'h'));

CREATE TABLE ldt_games (
		serialReference character varying(8) primary key,
		gameName character varying(50) NOT NULL,
		description text NOT NULL,
		rules text NOT NULL,
		minGamers int NOT NULL,
		maxGamers int NOT NULL,
		gameType character varying(10) NOT NULL,
		timeUnitAdd ldt_timeunit_domain NOT NULL,
		timeUnit ldt_timeunit_domain NOT NULL,
		costForUnit real NOT NULL,
		costForUnitAdd real NOT NULL,
		position character varying(10) NOT NULL,
		available boolean DEFAULT 't' NOT NULL
);

insert into ldt_games values ( '001', 'juego1', 'fdsafdsa', 'hafasds', 2, 4, 'Video', 'h', 'm', '1000', '100', '1', 't' );
insert into ldt_games values ( '002', 'juego2', 'fdsafdsa', 'hafasds', 2, 4, 'Video', 'h', 'm', '1000', '100', '1', 't' );
insert into ldt_games values ( '003', 'juego3', 'fdsafdsa', 'hafasds', 2, 4, 'Video', 'h', 'm', '1000', '100', '1', 't' );
insert into ldt_games values ( '004', 'juego4', 'fdsafdsa', 'hafasds', 2, 4, 'Video', 'h', 'm', '1000', '100', '1', 't' );
insert into ldt_games values ( '005', 'juego5', 'fdsafdsa', 'hafasds', 2, 4, 'Video', 'h', 'm', '1000', '100', '1', 't' );

CREATE TABLE ldt_persons (
		docIdent character varying(10)  primary key,
		firstName character varying(50) NOT NULL,
		lastName character varying(50) NOT NULL,
		phone character varying(15),
		cellular character varying(15),
		email character varying(60) check( email like '%@%.%' ),
		address character varying(40),
		genre ldt_genre_domain
		);
		
insert into ldt_persons values ( '001', 'Admin', 'gge34', '5586249', '54353', 'admin@heaven.org', 'fdsfdas', 'f' );
insert into ldt_persons values ( '002', 'dos', 'hg4', '5586249', '54353', 'afdsf@heaven.org', 'fdsfdas', 'f' );
insert into ldt_persons values ( '003', 'tres', '4hbx', '5586249', '54353', 'addmasin@heaven.org', 'fdsfdas', 'f' );
insert into ldt_persons values ( '004', 'cuatro', '5has', '5586249', '54353', 'asadmin@heaven.org', 'fdsfdas', 'f' );
insert into ldt_persons values ( '005', 'cinco', 'xx', '5586249', '54353', 'admbnrsin@heaven.org', 'fdsfdas', 'f' );
insert into ldt_persons values ( '006', 'seis', 'hgbna', '5586249', '54353', 'admdsingsas@heaven.org', 'fdsfdas', 'f' );
insert into ldt_persons values ( '007', 'siete', 'u5de', '5586249', '54353', 'adsmsain@heaven.org', 'fdsfdas', 'f' );
insert into ldt_persons values ( '008', 'ocho', 'u5de', '5586249', '54353', 'adsmsain@heaven.org', 'fdsfdas', 'f' );
insert into ldt_persons values ( '009', 'nueve', 'u5de', '5586249', '54353', 'adsmsain@heaven.org', 'fdsfdas', 'f' );
		
CREATE TABLE ldt_clients (
			docIdent character varying(10) references ldt_persons(docIdent)  on delete cascade on update cascade,
			inscriptionDate date NOT NULL,
			comment character varying(40),
			banned boolean default 'f',
			idReferencePerson character varying(10) references ldt_persons(docIdent),
			primary key(docIdent)
			);

insert into ldt_clients values ( '002', '01-jan-01', 'good', 'f', '003' );
insert into ldt_clients values ( '004', '01-jan-01', 'good', 'f', '005' );
insert into ldt_clients values ( '006', '01-jan-01', 'good', 'f', '007' );
insert into ldt_clients values ( '008', '01-jan-01', 'good', 'f', '009' );
			
CREATE TABLE ldt_users (
			docIdent character varying(10) references ldt_persons(docIdent) on delete cascade on update cascade,
			login character varying(20) primary key,
			permissions character varying(5) NOT NULL
			);
			
insert into ldt_users values ( '001', 'kladmin', '11111' );
			
CREATE TABLE ldt_tournament (
			name character varying(50) PRIMARY KEY,
			gameSerialReference character varying(8) references ldt_games(serialReference) on delete cascade on update cascade,
			initDate date NOT NULL,
			endDate date NOT NULL check (initDate <= endDate),
			roundsForPair integer NOT NULL,
			rounds integer NOT NULL,
			price real NOT NULL,
			discount real,
			active boolean DEFAULT 't' NOT NULL
			);
			
			
CREATE TABLE ldt_participates (
			clientDocIdent character varying(15) references ldt_clients(docIdent) on delete cascade on update cascade,
			codTournament character varying(50) references ldt_tournament(name) on delete cascade on update cascade,
			rank integer,
			primary key(clientDocIdent, codTournament)
			);
			
CREATE TABLE ldt_rents (
			clientDocIdent character varying(10) NOT NULL,
			gameSerialReference character varying(10) NOT NULL,
			rentHour time without time zone NOT NULL,
			units int NOT NULL,
			addunits int,
			date date NOT NULL,
			active boolean default 't' NOT NULL,
			primary key (gameSerialReference, date, rentHour),
			foreign key (clientDocIdent) references ldt_clients(docIdent) on delete cascade on update cascade,
			foreign key (gameSerialReference) references ldt_games(serialReference) on delete cascade on update cascade
			);
			
CREATE TABLE ldt_rounds (
			nRound integer NOT NULL,
			codTournament character varying(50) references ldt_tournament(name) on delete cascade on update cascade,
	
			primary key(nRound, codTournament)
			);
			
CREATE TABLE ldt_match (
			number integer,
			nRound integer,
			codTournament character varying(50),
			opponent1 character varying(10),
			resultOpp1 ldt_points_domain NOT NULL,
			opponent2 character varying(10),
			resultOpp2 ldt_points_domain,
			rest bool default 'f',
			primary key (number, codTournament),
			foreign key (nRound, codTournament) references ldt_rounds(nRound, codTournament) on delete cascade on update cascade,
			foreign key (opponent1,codTournament) references ldt_participates(clientDocIdent, codTournament) on delete cascade on update cascade,
			foreign key (opponent2,codTournament) references ldt_participates(clientDocIdent, codTournament) on delete cascade on update cascade
			);
			
CREATE TABLE ldt_enterprise (
			nit character varying(10) NOT NULL,
			address character varying(40),
			name character varying(50) NOT NULL,
			phone character varying(10),
			city character varying(15),
			primary key(nit)
);

create view ldt_users_view as SELECT firstname,lastname,login from ldt_users,ldt_persons where ldt_persons.docident in (select ldt_users.docident from ldt_persons );

create view ldt_tournament_view as select name,gamename,initdate,active from ldt_tournament,ldt_games where ldt_games.serialreference in ( select gameserialreference from ldt_games );

create view ldt_clients_view as SELECT ldt_clients.docIdent,firstname,lastname,banned from ldt_clients,ldt_persons where ldt_persons.docIdent in (select ldt_clients.docident from ldt_persons );

create view ldt_rents_view as select gameserialreference,clientdocident, gamename,firstname,lastname from ldt_games,ldt_persons,ldt_rents where ldt_persons.docident in ( select clientdocident from ldt_persons )  and serialreference  in ( select gameserialreference from ldt_games );

CREATE or replace FUNCTION ldt_updateGameAvail() returns trigger AS 'begin update ldt_games set available=not NEW.active where serialreference=NEW.gameserialreference; return NEW; end; 'language plpgsql;

CREATE or replace FUNCTION ldt_releaseGame() returns trigger AS ' begin update ldt_games  set available=''t'' where serialreference=OLD.gameserialreference; return OLD; end; 'language plpgsql;

CREATE TRIGGER ldt_addTournamentTrigger after insert or update on ldt_tournament for row execute procedure ldt_updateGameAvail();

CREATE TRIGGER ldt_rentGameTrigger after insert or update on ldt_rents for row execute procedure ldt_updateGameAvail();

CREATE TRIGGER ldt_delTournamentTrigger before delete on ldt_tournament for row execute procedure ldt_releaseGame();

CREATE TRIGGER ldt_delRentTrigger before delete on ldt_rents for row execute procedure ldt_releaseGame();

CREATE FUNCTION ldt_updateParticipants() returns trigger as
'declare 
	participants RECORD;
	ways RECORD;
begin 
	select into ways roundsforpair from ldt_tournament where name=NEW.codtournament;
	
	select into participants count(clientdocident)-1 as total from ldt_participates where codtournament=NEW.codtournament; 
	
	if ( (participants.total+1) % 2 = 0 )
	then
		participants.total := (participants.total)*ways.roundsforpair;
	else
		participants.total := (participants.total+1)*ways.roundsforpair;
	end if;
	
	update ldt_tournament set rounds=participants.total where name=NEW.codtournament;
	
	return NEW;
end;
'language plpgsql;

CREATE TRIGGER ldt_triggerparticipants after insert on ldt_participates for  row execute procedure ldt_updateParticipants();


-- VISTA DE RESULTADOS
drop view ldt_resultstable_view;
create or replace view ldt_resultstable_view as select codtournament as tournament, opponent1 as participant, win, draw,lost, total from

(
select codtournament, opponent1, sum(win1) as win
from (
SELECT ldt_participates.codtournament,opponent1,count(resultopp1) as win1 from ldt_match 
join ldt_participates on clientdocident=opponent1 and ldt_participates.codtournament=ldt_match.codtournament 
where resultopp1='3'
group by ldt_participates.codtournament,opponent1 

union 

SELECT ldt_participates.codtournament,opponent2,count(resultopp2) as win1 from ldt_match 
join ldt_participates on clientdocident=opponent2 and ldt_participates.codtournament=ldt_match.codtournament 
where resultopp2='3'
group by ldt_participates.codtournament,opponent2
) as tabletmp group by opponent1, codtournament
) as tablewin

full join 

(
select codtournament, opponent1, sum(draw1) as draw
from (
SELECT ldt_participates.codtournament,opponent1,count(resultopp1) as draw1 from ldt_match 
join ldt_participates on clientdocident=opponent1 and ldt_participates.codtournament=ldt_match.codtournament 
where resultopp1='1'
group by ldt_participates.codtournament,opponent1 

union 

SELECT ldt_participates.codtournament,opponent2,count(resultopp2) as draw1 from ldt_match 
join ldt_participates on clientdocident=opponent2 and ldt_participates.codtournament=ldt_match.codtournament 
where resultopp2='1'
group by ldt_participates.codtournament,opponent2
) as tabletmp group by opponent1, codtournament
) as tabledraw

using ( codtournament,opponent1 )

full join

(
select codtournament, opponent1, sum(lost1) as lost
from (
SELECT ldt_participates.codtournament,opponent1,count(resultopp1) as lost1 from ldt_match 
join ldt_participates on clientdocident=opponent1 and ldt_participates.codtournament=ldt_match.codtournament 
where resultopp1='0'
group by ldt_participates.codtournament,opponent1 

union 

SELECT ldt_participates.codtournament,opponent2,count(resultopp2) as lost1 from ldt_match 
join ldt_participates on clientdocident=opponent2 and ldt_participates.codtournament=ldt_match.codtournament 
where resultopp2='0'
group by ldt_participates.codtournament,opponent2
) as tabletmp group by opponent1, codtournament
) as tablelost


using ( codtournament,opponent1 )

join

(
select codtournament, opponent1, sum(subtotal) as total
from (
SELECT ldt_participates.codtournament,opponent1,sum(resultopp1) as subtotal from ldt_match 
join ldt_participates on clientdocident=opponent1 and ldt_participates.codtournament=ldt_match.codtournament 
group by ldt_participates.codtournament,opponent1 

union 

SELECT ldt_participates.codtournament,opponent2,sum(resultopp2) as subtotal from ldt_match 
join ldt_participates on clientdocident=opponent2 and ldt_participates.codtournament=ldt_match.codtournament 
group by ldt_participates.codtournament,opponent2
) as tabletmp group by opponent1, codtournament
) as tabletotal

using (codtournament,opponent1);

-- VISTA DE RESULTADOS --
