--
-- PostgreSQL database dump
--

SET client_encoding = 'SQL_ASCII';
SET check_function_bodies = false;

SET SESSION AUTHORIZATION 'postgres';

--
-- TOC entry 4 (OID 2200)
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
-- GRANT ALL ON SCHEMA public TO PUBLIC;

-- Cambiar esto segun el usuario
SET SESSION AUTHORIZATION 'kludoteca-admin';

SET search_path = public, pg_catalog;

--
-- TOC entry 5 (OID 221670)
-- Name: pga_graphs; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE pga_graphs (
    graphname character varying(64) NOT NULL,
    graphsource text,
    graphcode text
);


--
-- TOC entry 6 (OID 221677)
-- Name: pga_layout; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE pga_layout (
    tablename character varying(64) NOT NULL,
    nrcols smallint,
    colnames text,
    colwidth text
);


--
-- TOC entry 7 (OID 221684)
-- Name: pga_images; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE pga_images (
    imagename character varying(64) NOT NULL,
    imagesource text
);


--
-- TOC entry 8 (OID 221691)
-- Name: pga_queries; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE pga_queries (
    queryname character varying(64) NOT NULL,
    querytype character(1),
    querycommand text,
    querytables text,
    querylinks text,
    queryresults text,
    querycomments text
);


--
-- TOC entry 9 (OID 221698)
-- Name: pga_reports; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE pga_reports (
    reportname character varying(64) NOT NULL,
    reportsource text,
    reportbody text,
    reportprocs text,
    reportoptions text
);


--
-- TOC entry 10 (OID 221705)
-- Name: pga_forms; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE pga_forms (
    formname character varying(64) NOT NULL,
    formsource text
);


--
-- TOC entry 11 (OID 221712)
-- Name: pga_diagrams; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE pga_diagrams (
    diagramname character varying(64) NOT NULL,
    diagramtables text,
    diagramlinks text
);


--
-- TOC entry 12 (OID 221719)
-- Name: pga_scripts; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE pga_scripts (
    scriptname character varying(64) NOT NULL,
    scriptsource text
);


--
-- TOC entry 13 (OID 221737)
-- Name: ldt_games; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE ldt_games (
    serialReference character varying(8) NOT NULL,
    gameName character varying(10) NOT NULL,
    description text NOT NULL,
    rules text NOT NULL,
    minGamers smallint NOT NULL,
    maxGamers smallint NOT NULL,
    gameType character varying(10) NOT NULL,
    timeUnitAdd character varying(10) NOT NULL,
    timeUnit character varying(10) NOT NULL,
    costTM real NOT NULL,
    costTMA real NOT NULL,
    position character varying(10) NOT NULL,
    state character varying (10) NOT NULL,
    primary key(serialReference)
);


--
-- TOC entry 14 (OID 221737)
-- Name: ldt_games; Type: ACL; Schema: public; Owner: kludoteca-admin
--

-- REVOKE ALL ON TABLE ldt_games FROM PUBLIC;
SET SESSION AUTHORIZATION 'kludoteca-admin';

--
-- TOC entry 15 (OID 221746)
-- Name: ldt_clients; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE ldt_clients (
    docIdent character varying(10) NOT NULL,
    inscriptionDate date NOT NULL,
    firstName character varying(10) NOT NULL,
    lastName character varying(10) NOT NULL,
    phone character varying(15),
    celular character varying(15),
    state character varying(10),
    address character varying(20),
    namereference character varying(15),
    phonereference character varying(15),
    addressreference character varying(20),
    primary key(docIdent)
);

--
-- TOC entry 16 (OID 221754)
-- Name: ldt_tournament; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE ldt_tournament (
    codTournament character varying(10) NOT NULL,
    gameReference character varying(8) NOT NULL,
    name character varying(10) NOT NULL,
    initDate date NOT NULL,
    endDate date NOT NULL,
    roundsForPair integer NOT NULL,
    rounds integer NOT NULL,
    price real NOT NULL,
    discount real NOT NULL,
    state character varying(10) NOT NULL,
    primary key(codTournament),
    foreign key(gameReference) references ldt_games(serialReference)
);


--
-- TOC entry 17 (OID 221760)
-- Name: ldt_rents; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE ldt_rents (
    clientDocIdent character varying(10) NOT NULL,
    gameSerialReference character varying(10) NOT NULL,
    returnHour time without time zone NOT NULL,
    date date NOT NULL,
    foreign key (clientDocIdent) references ldt_clients(docIdent),
    foreign key (gameSerialReference) references ldt_games(serialReference)
);


--
-- TOC entry 18 (OID 221763)
-- Name: ldt_participates; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE ldt_participates (
    clientDocIdent character varying(15),
    codTournament character varying(10),
    foreign key (clientDocIdent) references ldt_clients(docIdent),
    foreign key (codTournament) references ldt_tournament(codTournament)

);


--
-- TOC entry 19 (OID 221769)
-- Name: ldt_users; Type: TABLE; Schema: public; Owner: kludoteca-admin
--

CREATE TABLE ldt_enterprise (
    nit character varying(10) NOT NULL,
    address character varying(20) NOT NULL,
    name character varying(10) NOT NULL,
    phone character varying(10) NOT NULL,
    city character varying(8) NOT NULL,
    primary key(nit)
);

CREATE TABLE ldt_users (
    docIdent character varying(10) NOT NULL,
    login character varying(10) NOT NULL,
    firstName character varying(10) NOT NULL,
    lastName character varying(10) NOT NULL,
    sex character varying(10) NOT NULL,
    address character varying(20) NOT NULL,
    phone character varying(10) NOT NULL,
    permissions character varying(10) NOT NULL,
    primary key(docIdent)
--    foreign key(login) references pg_user(usename)
);

--
-- Data for TOC entry 33 (OID 221670)
-- Name: pga_graphs; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY pga_graphs (graphname, graphsource, graphcode) FROM stdin;
\.


--
-- Data for TOC entry 34 (OID 221677)
-- Name: pga_layout; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY pga_layout (tablename, nrcols, colnames, colwidth) FROM stdin;
public.ldt_tournament	9	codTournament game name initDate endDate roundsForPair rounds price discount	150 150 150 150 150 150 150 150 150
public.ldt_clients	6	docIdent inscriptionDate firstName lastName phone celular	150 150 150 150 150 150
\.


--
-- Data for TOC entry 35 (OID 221684)
-- Name: pga_images; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY pga_images (imagename, imagesource) FROM stdin;
\.


--
-- Data for TOC entry 36 (OID 221691)
-- Name: pga_queries; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY pga_queries (queryname, querytype, querycommand, querytables, querylinks, queryresults, querycomments) FROM stdin;
\.


--
-- Data for TOC entry 37 (OID 221698)
-- Name: pga_reports; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY pga_reports (reportname, reportsource, reportbody, reportprocs, reportoptions) FROM stdin;
\.


--
-- Data for TOC entry 38 (OID 221705)
-- Name: pga_forms; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY pga_forms (formname, formsource) FROM stdin;
\.


--
-- Data for TOC entry 39 (OID 221712)
-- Name: pga_diagrams; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY pga_diagrams (diagramname, diagramtables, diagramlinks) FROM stdin;
\.


--
-- Data for TOC entry 40 (OID 221719)
-- Name: pga_scripts; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY pga_scripts (scriptname, scriptsource) FROM stdin;
\.


--
-- Data for TOC entry 41 (OID 221737)
-- Name: ldt_games; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY ldt_games (serialReference, gameName, description, rules, minGamers, maxGamers, gameType, timeUnitAdd, timeUnit, costTM, costTMA, position) FROM stdin;
\.


--
-- Data for TOC entry 42 (OID 221746)
-- Name: ldt_clients; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY ldt_clients (docIdent, inscriptionDate, firstName, lastName, phone, celular) FROM stdin;
\.


--
-- Data for TOC entry 43 (OID 221754)
-- Name: ldt_tournament; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY ldt_tournament (codTournament, gameReference, name, initDate, endDate, roundsForPair, rounds, price, discount) FROM stdin;
\.


--
-- Data for TOC entry 44 (OID 221760)
-- Name: ldt_rents; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY ldt_rents (clientDocIdent, gameSerialReference, returnHour, date) FROM stdin;
\.


--
-- Data for TOC entry 45 (OID 221763)
-- Name: ldt_participates; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY ldt_participates (clientDocIdent, codTournament) FROM stdin;
\.


--
-- Data for TOC entry 46 (OID 221769)
-- Name: ldt_users; Type: TABLE DATA; Schema: public; Owner: kludoteca-admin
--

COPY ldt_users (docIdent, firstName, lastName, sex, address, phone, permissions) FROM stdin;
\.

SET SESSION AUTHORIZATION 'postgres';

--
-- TOC entry 3 (OID 2200)
-- Name: SCHEMA public; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON SCHEMA public IS 'Standard public schema';




