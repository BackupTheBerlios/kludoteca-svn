<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>
<tagfile>
  <compound kind="page">
    <name>index</name>
    <title></title>
    <filename>index</filename>
    <docanchor file="index">casos</docanchor>
    <docanchor file="index">fac</docanchor>
    <docanchor file="index">actores</docanchor>
    <docanchor file="index">drkonq</docanchor>
    <docanchor file="index">func</docanchor>
    <docanchor file="index">riezgos</docanchor>
    <docanchor file="index">gui</docanchor>
    <docanchor file="index">imp</docanchor>
    <docanchor file="index">intro</docanchor>
    <docanchor file="index">req</docanchor>
    <docanchor file="index">leg</docanchor>
    <docanchor file="index">cliente</docanchor>
    <docanchor file="index">admin</docanchor>
    <docanchor file="index">fia</docanchor>
    <docanchor file="index">red</docanchor>
    <docanchor file="index">definition</docanchor>
    <docanchor file="index">sop</docanchor>
  </compound>
  <compound kind="class">
    <name>AdminDatabase</name>
    <filename>classAdminDatabase.html</filename>
    <base>LTListView</base>
    <member kind="slot">
      <type>void</type>
      <name>getClickedItem</name>
      <anchor>i0</anchor>
      <arglist>(QListViewItem *item)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addButtonClicked</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>delButtonClicked</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>modifyButtonClicked</name>
      <anchor>i3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>queryButtonClicked</name>
      <anchor>i4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addItem</name>
      <anchor>i5</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>slotFilter</name>
      <anchor>i6</anchor>
      <arglist>(const QString &amp;filter)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>updateItem</name>
      <anchor>i7</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AdminDatabase</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AdminDatabase</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fillList</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AdminUsers</name>
    <filename>classAdminUsers.html</filename>
    <base>LTListView</base>
    <member kind="slot">
      <type>void</type>
      <name>getClickedItem</name>
      <anchor>i0</anchor>
      <arglist>(QListViewItem *item)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addButtonClicked</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>delButtonClicked</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>modifyButtonClicked</name>
      <anchor>i3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>queryButtonClicked</name>
      <anchor>i4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addItem</name>
      <anchor>i5</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>slotFilter</name>
      <anchor>i6</anchor>
      <arglist>(const QString &amp;filter)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>updateItem</name>
      <anchor>i7</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AdminUsers</name>
      <anchor>a0</anchor>
      <arglist>(Button button1=NoButton, Button button2=NoButton, Button button3=NoButton, Button button4=NoButton, QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AdminUsers</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fillList</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AdminWidget</name>
    <filename>classAdminWidget.html</filename>
    <base>LTToolBox</base>
    <member kind="signal">
      <type>void</type>
      <name>sendWidget</name>
      <anchor>l0</anchor>
      <arglist>(KMdiChildView *)</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>message2osd</name>
      <anchor>l1</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AdminWidget</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AdminWidget</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ClientsWidget</name>
    <filename>classClientsWidget.html</filename>
    <base>LTListView</base>
    <member kind="slot">
      <type>void</type>
      <name>getClickedItem</name>
      <anchor>i0</anchor>
      <arglist>(QListViewItem *item)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addButtonClicked</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>delButtonClicked</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>modifyButtonClicked</name>
      <anchor>i3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>queryButtonClicked</name>
      <anchor>i4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addItem</name>
      <anchor>i5</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>updateItem</name>
      <anchor>i6</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ClientsWidget</name>
      <anchor>a0</anchor>
      <arglist>(Button button1=NoButton, Button button2=NoButton, Button button3=NoButton, Button button4=NoButton, QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fillList</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Crash</name>
    <filename>classCrash.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>crashHandler</name>
      <anchor>e0</anchor>
      <arglist>(int signal)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FDInitDatabase</name>
    <filename>classFDInitDatabase.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>createDatabase</name>
      <anchor>i0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>enableNext</name>
      <anchor>l0</anchor>
      <arglist>(QWidget *widget, bool e)</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>gotoFinish</name>
      <anchor>l1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FDInitDatabase</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FDInitDatabase</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>KLDatabase *</type>
      <name>getDatabaseConnection</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>checkAccount</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FDSetupAdmin</name>
    <filename>classFDSetupAdmin.html</filename>
    <member kind="function">
      <type></type>
      <name>FDSetupAdmin</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FDSetupAdmin</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setAdministrator</name>
      <anchor>a2</anchor>
      <arglist>(KLDatabase *db)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FDWelcome</name>
    <filename>classFDWelcome.html</filename>
    <member kind="function">
      <type></type>
      <name>FDWelcome</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FDWelcome</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMessage</name>
      <anchor>a2</anchor>
      <arglist>(const QString &amp;text)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormAdminClients</name>
    <filename>classFormAdminClients.html</filename>
    <base>FormBase</base>
    <member kind="slot">
      <type>void</type>
      <name>accept</name>
      <anchor>i0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>cancel</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>clean</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>message2osd</name>
      <anchor>l0</anchor>
      <arglist>(const QString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FormAdminClients</name>
      <anchor>a0</anchor>
      <arglist>(FormBase::Type t, QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FormAdminClients</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setupForm</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getClientId</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getClientName</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getSystemDate</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getClientLastName</name>
      <anchor>a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getClientPhone</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getClientCellular</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getClientState</name>
      <anchor>a9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getClientEmail</name>
      <anchor>a10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getClientSex</name>
      <anchor>a11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getClientAddress</name>
      <anchor>a12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getFriendId</name>
      <anchor>a13</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getFriendLastName</name>
      <anchor>a14</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getFriendName</name>
      <anchor>a15</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getFriendPhone</name>
      <anchor>a16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getFriendCellular</name>
      <anchor>a17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getFriendAddress</name>
      <anchor>a18</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getFriendState</name>
      <anchor>a19</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getFriendEmail</name>
      <anchor>a20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getFriendSex</name>
      <anchor>a21</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setClientId</name>
      <anchor>a22</anchor>
      <arglist>(const QString &amp;id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setClientName</name>
      <anchor>a23</anchor>
      <arglist>(const QString &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setClientLastName</name>
      <anchor>a24</anchor>
      <arglist>(const QString &amp;lastname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setClientPhone</name>
      <anchor>a25</anchor>
      <arglist>(const QString &amp;phone)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setClientCellular</name>
      <anchor>a26</anchor>
      <arglist>(const QString &amp;cell)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setClientState</name>
      <anchor>a27</anchor>
      <arglist>(const QString &amp;state)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setClientEmail</name>
      <anchor>a28</anchor>
      <arglist>(const QString &amp;email)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setClientSex</name>
      <anchor>a29</anchor>
      <arglist>(QString &amp;sex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setClientAddress</name>
      <anchor>a30</anchor>
      <arglist>(const QString &amp;address)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFriendId</name>
      <anchor>a31</anchor>
      <arglist>(const QString &amp;id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFriendName</name>
      <anchor>a32</anchor>
      <arglist>(const QString &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFriendLastName</name>
      <anchor>a33</anchor>
      <arglist>(const QString &amp;lastname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFriendPhone</name>
      <anchor>a34</anchor>
      <arglist>(const QString &amp;phone)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFriendCellular</name>
      <anchor>a35</anchor>
      <arglist>(const QString &amp;cell)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFriendState</name>
      <anchor>a36</anchor>
      <arglist>(const QString &amp;state)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFriendEmail</name>
      <anchor>a37</anchor>
      <arglist>(const QString &amp;email)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFriendSex</name>
      <anchor>a38</anchor>
      <arglist>(QString &amp;sex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFriendAddress</name>
      <anchor>a39</anchor>
      <arglist>(const QString &amp;address)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormAdminGame</name>
    <filename>classFormAdminGame.html</filename>
    <base>FormBase</base>
    <member kind="slot">
      <type>void</type>
      <name>accept</name>
      <anchor>i0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>cancel</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>clean</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>message2osd</name>
      <anchor>l0</anchor>
      <arglist>(const QString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FormAdminGame</name>
      <anchor>a0</anchor>
      <arglist>(FormBase::Type t, QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FormAdminGame</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fillField</name>
      <anchor>a2</anchor>
      <arglist>(QString explanation, QString name, QString description, QString rules, int numPlayer, QString type, double costUnit)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>formQuery</name>
      <anchor>a3</anchor>
      <arglist>(const QString &amp;idGame)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>formDelete</name>
      <anchor>a4</anchor>
      <arglist>(const QString &amp;idGame)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>formModify</name>
      <anchor>a5</anchor>
      <arglist>(const QString &amp;idGame)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getGameName</name>
      <anchor>a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getDescriptionGame</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getRulesGame</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getTypeGame</name>
      <anchor>a9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getStateGame</name>
      <anchor>a10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getReferenceGame</name>
      <anchor>a11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getTimeUnit</name>
      <anchor>a12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getTimeUnitAdd</name>
      <anchor>a13</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMinPlayers</name>
      <anchor>a14</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMaxPlayers</name>
      <anchor>a15</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getCostUnitTime</name>
      <anchor>a16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getCostTimeAdditional</name>
      <anchor>a17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGameName</name>
      <anchor>a18</anchor>
      <arglist>(const QString &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDescriptionGame</name>
      <anchor>a19</anchor>
      <arglist>(const QString &amp;description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRulesGame</name>
      <anchor>a20</anchor>
      <arglist>(const QString &amp;rules)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTypeGame</name>
      <anchor>a21</anchor>
      <arglist>(const QString &amp;type, int index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStateGame</name>
      <anchor>a22</anchor>
      <arglist>(const QString &amp;available)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setReferenceGame</name>
      <anchor>a23</anchor>
      <arglist>(const QString &amp;reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTimeUnit</name>
      <anchor>a24</anchor>
      <arglist>(const QString &amp;unitTime, int index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setUnitTimeAdd</name>
      <anchor>a25</anchor>
      <arglist>(const QString &amp;unitTimeAdd, int index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMinPlayers</name>
      <anchor>a26</anchor>
      <arglist>(const int &amp;numMinPlayers)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMaxPlayers</name>
      <anchor>a27</anchor>
      <arglist>(const int &amp;numMaxPlayers)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCostUnitTime</name>
      <anchor>a28</anchor>
      <arglist>(const double &amp;costTime)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCostTimeAdditional</name>
      <anchor>a29</anchor>
      <arglist>(const double &amp;costAditional)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>check</name>
      <anchor>a30</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>verification</name>
      <anchor>a31</anchor>
      <arglist>(const QString &amp;code)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QGridLayout *</type>
      <name>m_grid</name>
      <anchor>p0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormAdminRents</name>
    <filename>classFormAdminRents.html</filename>
    <base>FormBase</base>
    <member kind="slot">
      <type>void</type>
      <name>accept</name>
      <anchor>i0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>cancel</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>clean</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>idTextEdit</name>
      <anchor>i3</anchor>
      <arglist>(int id)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>setCltTable</name>
      <anchor>i4</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>setGameTable</name>
      <anchor>i5</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>message2osd</name>
      <anchor>l0</anchor>
      <arglist>(const QString &amp;msg)</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>changedTextEdit</name>
      <anchor>l1</anchor>
      <arglist>(int id)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FormAdminRents</name>
      <anchor>a0</anchor>
      <arglist>(FormBase::Type t, QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setupForm</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormAdminUsers</name>
    <filename>classFormAdminUsers.html</filename>
    <base>FormBase</base>
    <member kind="slot">
      <type>void</type>
      <name>accept</name>
      <anchor>i0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>cancel</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>clean</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>message2osd</name>
      <anchor>l0</anchor>
      <arglist>(const QString &amp;msg)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FormAdminUsers</name>
      <anchor>a0</anchor>
      <arglist>(FormBase::Type t, QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FormAdminUsers</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setupForm</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getIdentification</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getLogin</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getPassword</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getFirstName</name>
      <anchor>a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getLastName</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getGenre</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getAddress</name>
      <anchor>a9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getPhone</name>
      <anchor>a10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getEmail</name>
      <anchor>a11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getPermissions</name>
      <anchor>a12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIdentification</name>
      <anchor>a13</anchor>
      <arglist>(const QString &amp;ident)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLogin</name>
      <anchor>a14</anchor>
      <arglist>(const QString &amp;login)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPassword</name>
      <anchor>a15</anchor>
      <arglist>(const QString &amp;pass)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFirstName</name>
      <anchor>a16</anchor>
      <arglist>(const QString &amp;fname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLastName</name>
      <anchor>a17</anchor>
      <arglist>(const QString &amp;lname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGenre</name>
      <anchor>a18</anchor>
      <arglist>(QString &amp;sex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAddress</name>
      <anchor>a19</anchor>
      <arglist>(const QString &amp;addrs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPhone</name>
      <anchor>a20</anchor>
      <arglist>(const QString &amp;phone)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEmail</name>
      <anchor>a21</anchor>
      <arglist>(const QString &amp;email)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPermissions</name>
      <anchor>a22</anchor>
      <arglist>(const QString &amp;perms)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>validateFields</name>
      <anchor>a23</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormBase</name>
    <filename>classFormBase.html</filename>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>accept</name>
      <anchor>i0</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>cancel</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>wasExecuted</name>
      <anchor>i2</anchor>
      <arglist>(bool good)</arglist>
    </member>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>clean</name>
      <anchor>i3</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="signal" virtualness="virtual">
      <type>virtual void</type>
      <name>sendQuery</name>
      <anchor>l0</anchor>
      <arglist>(KLQuery *)</arglist>
    </member>
    <member kind="signal" virtualness="virtual">
      <type>virtual void</type>
      <name>sendRawQuery</name>
      <anchor>l1</anchor>
      <arglist>(const QString &amp;sql)</arglist>
    </member>
    <member kind="signal" virtualness="virtual">
      <type>virtual void</type>
      <name>accepted</name>
      <anchor>l2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="signal" virtualness="virtual">
      <type>virtual void</type>
      <name>cancelled</name>
      <anchor>l3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="signal" virtualness="virtual">
      <type>virtual void</type>
      <name>inserted</name>
      <anchor>l4</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FormBase</name>
      <anchor>a0</anchor>
      <arglist>(KLDatabase *db, QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FormBase</name>
      <anchor>a1</anchor>
      <arglist>(Type t, QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FormBase</name>
      <anchor>a2</anchor>
      <arglist>(Button button1=NoButton, Button button2=NoButton, QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FormBase</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTitle</name>
      <anchor>a4</anchor>
      <arglist>(QString newTitle)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setType</name>
      <anchor>a5</anchor>
      <arglist>(Type t)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getType</name>
      <anchor>a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTitleFont</name>
      <anchor>a7</anchor>
      <arglist>(QString font, int fontsize)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setExplanation</name>
      <anchor>a8</anchor>
      <arglist>(QString newExplanation)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setupForm</name>
      <anchor>a9</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setupButtons</name>
      <anchor>a10</anchor>
      <arglist>(Button button1, Button button2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTextAcceptButton</name>
      <anchor>a11</anchor>
      <arglist>(QString newText)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTextCancelButton</name>
      <anchor>a12</anchor>
      <arglist>(QString newText)</arglist>
    </member>
    <member kind="function">
      <type>QWidget *</type>
      <name>setupLineEdit</name>
      <anchor>a13</anchor>
      <arglist>(QWidget *parent, QString text, int lineEditWidth=200)</arglist>
    </member>
    <member kind="function">
      <type>HashLineEdit</type>
      <name>setupGridLineEdit</name>
      <anchor>a14</anchor>
      <arglist>(QWidget *parent, QStringList texts, int lineEditWidth=200, QStringList names=QStringList())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addLineEdits</name>
      <anchor>a15</anchor>
      <arglist>(QWidget *parent, QStringList texts, HashLineEdit &amp;hle, int lineEditWidth, QStringList names=QStringList())</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>lastQueryWasGood</name>
      <anchor>a16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QString</type>
      <name>getSystemDate</name>
      <anchor>a17</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormMatchOrder</name>
    <filename>classFormMatchOrder.html</filename>
    <base>FormBase</base>
    <member kind="function">
      <type></type>
      <name>FormMatchOrder</name>
      <anchor>a0</anchor>
      <arglist>(const QString &amp;tournament, int nround, FormBase::Type t, QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setupForm</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>accept</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cancel</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>updateRanks</name>
      <anchor>a6</anchor>
      <arglist>(const QStringList &amp;clients)</arglist>
    </member>
    <member kind="function">
      <type>QStringList</type>
      <name>getMatchResult</name>
      <anchor>a7</anchor>
      <arglist>(int number)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormParticipants</name>
    <filename>classFormParticipants.html</filename>
    <base>FormBase</base>
    <member kind="slot">
      <type>void</type>
      <name>fillClientInformation</name>
      <anchor>i0</anchor>
      <arglist>(const QString &amp;key)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addParticipant</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>removeParticipant</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>fillTableInformation</name>
      <anchor>i3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>message2osd</name>
      <anchor>l0</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FormParticipants</name>
      <anchor>a0</anchor>
      <arglist>(const QString &amp;tournament, FormBase::Type t, QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTournament</name>
      <anchor>a2</anchor>
      <arglist>(const QString &amp;tournament)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setupForm</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>accept</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>cancel</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>clean</name>
      <anchor>a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QStringList</type>
      <name>getAllClients</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormQueryTournament</name>
    <filename>classFormQueryTournament.html</filename>
    <base>FormBase</base>
    <member kind="function">
      <type></type>
      <name>FormQueryTournament</name>
      <anchor>a0</anchor>
      <arglist>(const QString &amp;tournament, QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setupForm</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>accept</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fillTable</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormTournament</name>
    <filename>classFormTournament.html</filename>
    <base>FormBase</base>
    <member kind="slot">
      <type>void</type>
      <name>accept</name>
      <anchor>i0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>cancel</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>clean</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>message2osd</name>
      <anchor>l0</anchor>
      <arglist>(const QString &amp;osd)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FormTournament</name>
      <anchor>a0</anchor>
      <arglist>(Type t, QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FormTournament</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setupForm</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTournamentName</name>
      <anchor>a3</anchor>
      <arglist>(const QString &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRounds</name>
      <anchor>a4</anchor>
      <arglist>(const QString &amp;rounds)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRounds4pair</name>
      <anchor>a5</anchor>
      <arglist>(const QString &amp;rounds)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPrice</name>
      <anchor>a6</anchor>
      <arglist>(const QString &amp;price)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDiscount</name>
      <anchor>a7</anchor>
      <arglist>(const QString &amp;discount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setInitDate</name>
      <anchor>a8</anchor>
      <arglist>(const QDate &amp;date)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEndDate</name>
      <anchor>a9</anchor>
      <arglist>(const QDate &amp;date)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getTournamentName</name>
      <anchor>a10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getRounds</name>
      <anchor>a11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getRounds4pair</name>
      <anchor>a12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getPrice</name>
      <anchor>a13</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getDiscount</name>
      <anchor>a14</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getInitDate</name>
      <anchor>a15</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getEndDate</name>
      <anchor>a16</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GamesList</name>
    <filename>classGamesList.html</filename>
    <base>LTListView</base>
    <member kind="slot">
      <type>void</type>
      <name>addGame</name>
      <anchor>i0</anchor>
      <arglist>(const QString &amp;game)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>getClickedItem</name>
      <anchor>i1</anchor>
      <arglist>(QListViewItem *item)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addButtonClicked</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>delButtonClicked</name>
      <anchor>i3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>modifyButtonClicked</name>
      <anchor>i4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>queryButtonClicked</name>
      <anchor>i5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>updateItem</name>
      <anchor>i6</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addItem</name>
      <anchor>i7</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>slotFilter</name>
      <anchor>i8</anchor>
      <arglist>(const QString &amp;filter)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GamesList</name>
      <anchor>a0</anchor>
      <arglist>(Button button1=NoButton, Button button2=NoButton, Button button3=NoButton, Button button4=NoButton, QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~GamesList</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setupListView</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fillList</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GamesModule</name>
    <filename>classGamesModule.html</filename>
    <member kind="function">
      <type></type>
      <name>GamesModule</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parentWidget=0L, const char *name=0L, WFlags f=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~GamesModule</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLDatabase</name>
    <filename>classKLDatabase.html</filename>
    <member kind="slot">
      <type>KLResultSet</type>
      <name>execQuery</name>
      <anchor>i0</anchor>
      <arglist>(KLQuery *query)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>execRawQuery</name>
      <anchor>i1</anchor>
      <arglist>(const QString &amp;sql)</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>progress</name>
      <anchor>l0</anchor>
      <arglist>(int p)</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>executed</name>
      <anchor>l1</anchor>
      <arglist>(bool good)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KLDatabase</name>
      <anchor>a0</anchor>
      <arglist>(QObject *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KLDatabase</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>KLResultSet</type>
      <name>execQuery</name>
      <anchor>a2</anchor>
      <arglist>(const QString &amp;consult, QStringList fields=QStringList())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDatabaseName</name>
      <anchor>a3</anchor>
      <arglist>(const QString &amp;dbname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setUserName</name>
      <anchor>a4</anchor>
      <arglist>(const QString &amp;login)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPassword</name>
      <anchor>a5</anchor>
      <arglist>(const QString &amp;password)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setHostName</name>
      <anchor>a6</anchor>
      <arglist>(const QString &amp;host)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPort</name>
      <anchor>a7</anchor>
      <arglist>(int p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setupConnection</name>
      <anchor>a8</anchor>
      <arglist>(const QString &amp;dbname, const QString &amp;login, const QString &amp;password, const QString &amp;host)</arglist>
    </member>
    <member kind="function">
      <type>KLResultSet</type>
      <name>select</name>
      <anchor>a9</anchor>
      <arglist>(QStringList fields, QString table, QString selectparams=QString::null)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>createTables</name>
      <anchor>a10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>dropTables</name>
      <anchor>a11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isLastError</name>
      <anchor>a12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static KLDatabase *</type>
      <name>instance</name>
      <anchor>e0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLDelete</name>
    <filename>classKLDelete.html</filename>
    <base>KLQuery</base>
    <member kind="function">
      <type></type>
      <name>KLDelete</name>
      <anchor>a0</anchor>
      <arglist>(QString table)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KLDelete</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLFirstDialog</name>
    <filename>classKLFirstDialog.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>next</name>
      <anchor>i0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>finished</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>showFinish</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>cancel</name>
      <anchor>i3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KLFirstDialog</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KLFirstDialog</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLInsert</name>
    <filename>classKLInsert.html</filename>
    <base>KLQuery</base>
    <member kind="function">
      <type></type>
      <name>KLInsert</name>
      <anchor>a0</anchor>
      <arglist>(QString table, QStringList values)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KLInsert</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLLogger</name>
    <filename>classKLLogger.html</filename>
    <member kind="function">
      <type>void</type>
      <name>setFile</name>
      <anchor>a2</anchor>
      <arglist>(const QString &amp;filename)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>log</name>
      <anchor>a3</anchor>
      <arglist>(const QString &amp;message, LogType t=Inf)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setupLogger</name>
      <anchor>a4</anchor>
      <arglist>(const QString &amp;directory, const QString &amp;filename)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static KLLogger *</type>
      <name>instance</name>
      <anchor>e0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLMainPage</name>
    <filename>classKLMainPage.html</filename>
    <member kind="signal">
      <type>void</type>
      <name>sendWidget</name>
      <anchor>l0</anchor>
      <arglist>(KMdiChildView *)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KLMainPage</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parentWidget, const char *widgetName, QObject *parent, const char *name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KLMainPage</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>openURL</name>
      <anchor>a2</anchor>
      <arglist>(const KURL &amp;url)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>openFile</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>saveState</name>
      <anchor>a4</anchor>
      <arglist>(QDataStream &amp;stream)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>restoreState</name>
      <anchor>a5</anchor>
      <arglist>(QDataStream &amp;stream)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addTournament</name>
      <anchor>a6</anchor>
      <arglist>(const QString &amp;name=QString::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addClient</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>urlSelected</name>
      <anchor>b0</anchor>
      <arglist>(const QString &amp;url, int button, int state, const QString &amp;target, KParts::URLArgs args=KParts::URLArgs())</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLMainPageFactory</name>
    <filename>classKLMainPageFactory.html</filename>
    <member kind="function">
      <type></type>
      <name>KLMainPageFactory</name>
      <anchor>a0</anchor>
      <arglist>(QObject *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static QString</type>
      <name>mainpage</name>
      <anchor>e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static QString</type>
      <name>page2</name>
      <anchor>e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static QString</type>
      <name>page3</name>
      <anchor>e2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static QString</type>
      <name>page4</name>
      <anchor>e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static QString</type>
      <name>page5</name>
      <anchor>e4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLPermission</name>
    <filename>classKLPermission.html</filename>
    <member kind="function">
      <type>void</type>
      <name>string2perms</name>
      <anchor>a2</anchor>
      <arglist>(const QString &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>activeAdminModule</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>activeClientsModule</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>activeGamesModule</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>activeTournamentModule</name>
      <anchor>a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>activeRentsModule</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static KLPermission *</type>
      <name>instance</name>
      <anchor>e0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLQuery</name>
    <filename>classKLQuery.html</filename>
    <member kind="function">
      <type></type>
      <name>~KLQuery</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QString</type>
      <name>getQuery</name>
      <anchor>a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setWhere</name>
      <anchor>a2</anchor>
      <arglist>(const QString &amp;w)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setCondition</name>
      <anchor>a3</anchor>
      <arglist>(const QString &amp;condition)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getType</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>KLQuery</name>
      <anchor>b0</anchor>
      <arglist>(Type t=Select)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QString</type>
      <name>m_query</name>
      <anchor>p0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QString</type>
      <name>m_cwhere</name>
      <anchor>p1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLResultSet</name>
    <filename>classKLResultSet.html</filename>
    <member kind="function">
      <type></type>
      <name>KLResultSet</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KLResultSet</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRecord</name>
      <anchor>a2</anchor>
      <arglist>(QStringList &amp;fields, QStringList &amp;results)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLResultSetInterpreter</name>
    <filename>classKLResultSetInterpreter.html</filename>
    <member kind="signal">
      <type>void</type>
      <name>readRecord</name>
      <anchor>l0</anchor>
      <arglist>(QStringList results)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KLResultSetInterpreter</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KLResultSetInterpreter</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>startElement</name>
      <anchor>a2</anchor>
      <arglist>(const QString &amp;, const QString &amp;, const QString &amp;qname, const QXmlAttributes &amp;atts)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>endElement</name>
      <anchor>a3</anchor>
      <arglist>(const QString &amp;ns, const QString &amp;localname, const QString &amp;qname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>characters</name>
      <anchor>a4</anchor>
      <arglist>(const QString &amp;ch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParseType</name>
      <anchor>a5</anchor>
      <arglist>(Type type)</arglist>
    </member>
    <member kind="function">
      <type>KLSqlResults</type>
      <name>getResults</name>
      <anchor>a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QStringList</type>
      <name>getResultList</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLSelect</name>
    <filename>classKLSelect.html</filename>
    <base>KLQuery</base>
    <member kind="function">
      <type></type>
      <name>KLSelect</name>
      <anchor>a0</anchor>
      <arglist>(QStringList fields, QStringList tables, bool dist=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KLSelect</name>
      <anchor>a1</anchor>
      <arglist>(QStringList fields, const QString &amp;table, bool dist=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KLSelect</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addSubConsult</name>
      <anchor>a3</anchor>
      <arglist>(QString connector, const KLSelect &amp;subconsult)</arglist>
    </member>
    <member kind="function">
      <type>QStringList</type>
      <name>getFields</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getQuery</name>
      <anchor>a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addFilter</name>
      <anchor>a6</anchor>
      <arglist>(const QString &amp;filter, QStringList fields=QStringList())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setOrderBy</name>
      <anchor>a7</anchor>
      <arglist>(const QString &amp;field, Order o)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setOrderBy</name>
      <anchor>a8</anchor>
      <arglist>(int field, Order o)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setJoin</name>
      <anchor>a9</anchor>
      <arglist>(const QString &amp;link, JoinConnector jc, const QStringList &amp;rest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLTable</name>
    <filename>classKLTable.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>fixSize</name>
      <anchor>i0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>expandTableSize</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>redimensionTable</name>
      <anchor>i2</anchor>
      <arglist>(int rows)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>insertRowData</name>
      <anchor>i3</anchor>
      <arglist>(const QStringList &amp;data, int row=-1)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>setViewportText</name>
      <anchor>i4</anchor>
      <arglist>(const QString &amp;text)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KLTable</name>
      <anchor>a0</anchor>
      <arglist>(int rows, int cols, QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KLTable</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resizeEvent</name>
      <anchor>a2</anchor>
      <arglist>(QResizeEvent *e)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setHeaderHText</name>
      <anchor>a3</anchor>
      <arglist>(int col, const QString &amp;text)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>drawContents</name>
      <anchor>a4</anchor>
      <arglist>(QPainter *p, int cx, int cy, int cw, int ch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>paintEvent</name>
      <anchor>a5</anchor>
      <arglist>(QPaintEvent *event)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>paintRow</name>
      <anchor>a6</anchor>
      <arglist>(int row, const QColor &amp;color)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>paintCell</name>
      <anchor>a7</anchor>
      <arglist>(QPainter *p, int row, int col, const QRect &amp;cr, bool selected, const QColorGroup &amp;cg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLudoteca</name>
    <filename>classKLudoteca.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>showValidateUser</name>
      <anchor>i0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KLudoteca</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~KLudoteca</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QSqlDatabase *</type>
      <name>getDatabase</name>
      <anchor>a2</anchor>
      <arglist>(const QString &amp;bdname, bool open=false)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>dragEnterEvent</name>
      <anchor>b0</anchor>
      <arglist>(QDragEnterEvent *event)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>dropEvent</name>
      <anchor>b1</anchor>
      <arglist>(QDropEvent *event)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>saveProperties</name>
      <anchor>b2</anchor>
      <arglist>(KConfig *)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>readProperties</name>
      <anchor>b3</anchor>
      <arglist>(KConfig *)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLudotecaPreferences</name>
    <filename>classKLudotecaPreferences.html</filename>
    <member kind="function">
      <type></type>
      <name>KLudotecaPreferences</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLudotecaPrefPageOne</name>
    <filename>classKLudotecaPrefPageOne.html</filename>
    <member kind="function">
      <type></type>
      <name>KLudotecaPrefPageOne</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KLudotecaPrefPageOne</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLudotecaPrefPageTwo</name>
    <filename>classKLudotecaPrefPageTwo.html</filename>
    <member kind="function">
      <type></type>
      <name>KLudotecaPrefPageTwo</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLudotecaView</name>
    <filename>classKLudotecaView.html</filename>
    <member kind="function">
      <type></type>
      <name>KLudotecaView</name>
      <anchor>a0</anchor>
      <arglist>(const QString &amp;caption, QWidget *parentWidget=0L, const char *name=0L, WFlags f=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~KLudotecaView</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print</name>
      <anchor>a2</anchor>
      <arglist>(QPainter *, int height, int width)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMessage</name>
      <anchor>a3</anchor>
      <arglist>(const QString &amp;texto)</arglist>
    </member>
    <member kind="function">
      <type>KLMainPage *</type>
      <name>mainPage</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addTournament</name>
      <anchor>a5</anchor>
      <arglist>(const QString &amp;texto=QString::null)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addClient</name>
      <anchor>a6</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLUpdate</name>
    <filename>classKLUpdate.html</filename>
    <base>KLQuery</base>
    <member kind="function">
      <type></type>
      <name>KLUpdate</name>
      <anchor>a0</anchor>
      <arglist>(QString table, QStringList fields, QStringList values)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KLUpdate</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>KLXmlReader</name>
    <filename>classKLXmlReader.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>analizeXml</name>
      <anchor>a2</anchor>
      <arglist>(const QXmlInputSource *input, KLResultSetInterpreter::Type t)</arglist>
    </member>
    <member kind="function">
      <type>KLSqlResults</type>
      <name>results</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QStringList</type>
      <name>getResultsList</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parse</name>
      <anchor>a5</anchor>
      <arglist>(const QXmlInputSource *input, bool incremental)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parse</name>
      <anchor>a6</anchor>
      <arglist>(const QXmlInputSource *input)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>LDTApp</name>
    <filename>classLDTApp.html</filename>
    <member kind="function">
      <type></type>
      <name>LDTApp</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LDTApp</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>firstDialog</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>KConfig *</type>
      <name>config</name>
      <anchor>a3</anchor>
      <arglist>(const QString &amp;group=&quot;General&quot;)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>appversion</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>applyColors</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>LTListView</name>
    <filename>classLTListView.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>setButtonText</name>
      <anchor>i0</anchor>
      <arglist>(Button b, const QString &amp;text)</arglist>
    </member>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>getClickedItem</name>
      <anchor>i1</anchor>
      <arglist>(QListViewItem *item)=0</arglist>
    </member>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>addButtonClicked</name>
      <anchor>i2</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>delButtonClicked</name>
      <anchor>i3</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>modifyButtonClicked</name>
      <anchor>i4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>queryButtonClicked</name>
      <anchor>i5</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>putItems</name>
      <anchor>i6</anchor>
      <arglist>(QStringList items)</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>addItem</name>
      <anchor>i7</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>slotSetFilterTimeout</name>
      <anchor>i8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>slotSetFilter</name>
      <anchor>i9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>slotFilter</name>
      <anchor>i10</anchor>
      <arglist>(const QString &amp;filter)</arglist>
    </member>
    <member kind="signal" virtualness="virtual">
      <type>virtual void</type>
      <name>message2osd</name>
      <anchor>l0</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="signal" virtualness="virtual">
      <type>virtual void</type>
      <name>sendWidget</name>
      <anchor>l1</anchor>
      <arglist>(KMdiChildView *)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LTListView</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LTListView</name>
      <anchor>a1</anchor>
      <arglist>(QStringList colsText, Button button1=NoButton, Button button2=NoButton, Button button3=NoButton, Button button4=NoButton, QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>makeButtons</name>
      <anchor>a3</anchor>
      <arglist>(Button button1, Button button2, Button button3, Button button4)</arglist>
    </member>
    <member kind="function">
      <type>KListView *</type>
      <name>getListView</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDatabase</name>
      <anchor>a5</anchor>
      <arglist>(KLDatabase *db)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>makeList</name>
      <anchor>a6</anchor>
      <arglist>(QStringList colsText)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>fillList</name>
      <anchor>a7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>KLListView *</type>
      <name>m_listView</name>
      <anchor>p0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>KLDatabase *</type>
      <name>m_db</name>
      <anchor>p1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>KLResultSetInterpreter *</type>
      <name>m_rsinterpreter</name>
      <anchor>p2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>KLXmlReader</type>
      <name>m_xmlreader</name>
      <anchor>p3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QXmlInputSource</type>
      <name>m_xmlsource</name>
      <anchor>p4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QString</type>
      <name>m_filterText</name>
      <anchor>p5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>LTToolBox</name>
    <filename>classLTToolBox.html</filename>
    <member kind="signal" virtualness="virtual">
      <type>virtual void</type>
      <name>sendWidget</name>
      <anchor>l0</anchor>
      <arglist>(KMdiChildView *)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LTToolBox</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LTToolBox</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>setupTabs</name>
      <anchor>b0</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MatchGenerator</name>
    <filename>classMatchGenerator.html</filename>
    <member kind="function">
      <type></type>
      <name>MatchGenerator</name>
      <anchor>a1</anchor>
      <arglist>(const MatchClientInfo &amp;mci, const QString &amp;tournament)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMatchClientInfo</name>
      <anchor>a3</anchor>
      <arglist>(const MatchClientInfo &amp;mci, const QString &amp;tournament)</arglist>
    </member>
    <member kind="function">
      <type>StringVector</type>
      <name>generate</name>
      <anchor>a4</anchor>
      <arglist>(Type t)</arglist>
    </member>
    <member kind="function">
      <type>StringVector</type>
      <name>qstringlist2stringvector</name>
      <anchor>a5</anchor>
      <arglist>(const QStringList &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>verifyPairs</name>
      <anchor>a6</anchor>
      <arglist>(StringVector &amp;sv)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>parent</name>
      <anchor>b0</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>left</name>
      <anchor>b1</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>rigth</name>
      <anchor>b2</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>maxHeapify</name>
      <anchor>b3</anchor>
      <arglist>(QStringList &amp;list, int i)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>buildMaxHeap</name>
      <anchor>b4</anchor>
      <arglist>(QStringList &amp;list)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>heapsort</name>
      <anchor>b5</anchor>
      <arglist>(QStringList &amp;list)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>swap</name>
      <anchor>b6</anchor>
      <arglist>(QStringList &amp;list, int i1, int i2)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ParticipantsList</name>
    <filename>classParticipantsList.html</filename>
    <base>LTListView</base>
    <member kind="slot">
      <type>void</type>
      <name>fillList</name>
      <anchor>i0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>getClickedItem</name>
      <anchor>i1</anchor>
      <arglist>(QListViewItem *item)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addButtonClicked</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>delButtonClicked</name>
      <anchor>i3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>modifyButtonClicked</name>
      <anchor>i4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>queryButtonClicked</name>
      <anchor>i5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addItem</name>
      <anchor>i6</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>slotFilter</name>
      <anchor>i7</anchor>
      <arglist>(const QString &amp;filter)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>updateItem</name>
      <anchor>i8</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ParticipantsList</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ParticipantsList</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RentsWidget</name>
    <filename>classRentsWidget.html</filename>
    <base>LTListView</base>
    <member kind="slot">
      <type>void</type>
      <name>getClickedItem</name>
      <anchor>i0</anchor>
      <arglist>(QListViewItem *item)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addButtonClicked</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>delButtonClicked</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>modifyButtonClicked</name>
      <anchor>i3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>queryButtonClicked</name>
      <anchor>i4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RentsWidget</name>
      <anchor>a0</anchor>
      <arglist>(Button button1=NoButton, Button button2=NoButton, Button button3=NoButton, Button button4=NoButton, QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fillList</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>slotFilter</name>
      <anchor>a3</anchor>
      <arglist>(const QString &amp;filter)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addItem</name>
      <anchor>a4</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RoundList</name>
    <filename>classRoundList.html</filename>
    <base>LTListView</base>
    <member kind="slot">
      <type>void</type>
      <name>fillList</name>
      <anchor>i0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RoundList</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addButtonClicked</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>delButtonClicked</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getClickedItem</name>
      <anchor>a4</anchor>
      <arglist>(QListViewItem *item)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>modifyButtonClicked</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>queryButtonClicked</name>
      <anchor>a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>tournamentFinished</name>
      <anchor>a7</anchor>
      <arglist>(const QString &amp;tname, int round)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TournamentActive</name>
    <filename>classTournamentActive.html</filename>
    <base>LTListView</base>
    <member kind="slot">
      <type>void</type>
      <name>getClickedItem</name>
      <anchor>i0</anchor>
      <arglist>(QListViewItem *item)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addButtonClicked</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>delButtonClicked</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>modifyButtonClicked</name>
      <anchor>i3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>queryButtonClicked</name>
      <anchor>i4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>tournamentModified</name>
      <anchor>l0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TournamentActive</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TournamentActive</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addItem</name>
      <anchor>a2</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>slotFilter</name>
      <anchor>a3</anchor>
      <arglist>(const QString &amp;filter)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>fillList</name>
      <anchor>b0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TournamentModule</name>
    <filename>classTournamentModule.html</filename>
    <member kind="function">
      <type></type>
      <name>TournamentModule</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TournamentModule</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TournamentOld</name>
    <filename>classTournamentOld.html</filename>
    <base>LTListView</base>
    <member kind="slot">
      <type>void</type>
      <name>getClickedItem</name>
      <anchor>i0</anchor>
      <arglist>(QListViewItem *item)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>addButtonClicked</name>
      <anchor>i1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>delButtonClicked</name>
      <anchor>i2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>modifyButtonClicked</name>
      <anchor>i3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>queryButtonClicked</name>
      <anchor>i4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TournamentOld</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TournamentOld</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fillList</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TournamentTabBar</name>
    <filename>classTournamentTabBar.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>applyChangesToLists</name>
      <anchor>i0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TournamentTabBar</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0, const char *name=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TournamentWidget</name>
    <filename>classTournamentWidget.html</filename>
    <base>LTToolBox</base>
    <member kind="function">
      <type></type>
      <name>TournamentWidget</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TournamentWidget</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ListLTListView</type>
      <name>listViews</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ValidateUser</name>
    <filename>classValidateUser.html</filename>
    <member kind="function">
      <type></type>
      <name>ValidateUser</name>
      <anchor>a0</anchor>
      <arglist>(QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>slotOk</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeConfig</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>Screenshoots</name>
    <title></title>
    <filename>Screenshoots</filename>
    <docanchor file="Screenshoots">juegos</docanchor>
    <docanchor file="Screenshoots">usuarios</docanchor>
  </compound>
  <compound kind="dir">
    <name>/home/krawek/Proyectos/kludoteca/src/admin-module/</name>
    <path>/home/krawek/Proyectos/kludoteca/src/admin-module/</path>
    <filename>dir_000002.html</filename>
    <file>admindatabase.cpp</file>
    <file>admindatabase.h</file>
    <file>adminusers.cpp</file>
    <file>adminusers.h</file>
    <file>adminwidget.cpp</file>
    <file>adminwidget.h</file>
    <file>formadminusers.cpp</file>
    <file>formadminusers.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/krawek/Proyectos/kludoteca/src/clients-module/</name>
    <path>/home/krawek/Proyectos/kludoteca/src/clients-module/</path>
    <filename>dir_000003.html</filename>
    <file>clientswidget.cpp</file>
    <file>clientswidget.h</file>
    <file>formadminclients.cpp</file>
    <file>formadminclients.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/krawek/Proyectos/kludoteca/src/games-module/</name>
    <path>/home/krawek/Proyectos/kludoteca/src/games-module/</path>
    <filename>dir_000005.html</filename>
    <file>formadmingame.cpp</file>
    <file>formadmingame.h</file>
    <file>gameslist.cpp</file>
    <file>gameslist.h</file>
    <file>gamesmodule.cpp</file>
    <file>gamesmodule.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/krawek/Proyectos/kludoteca/</name>
    <path>/home/krawek/Proyectos/kludoteca/</path>
    <filename>dir_000000.html</filename>
    <dir>/home/krawek/Proyectos/kludoteca/src/</dir>
    <file>config.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/krawek/Proyectos/kludoteca/src/lib/</name>
    <path>/home/krawek/Proyectos/kludoteca/src/lib/</path>
    <filename>dir_000004.html</filename>
    <file>createdatabase.cpp</file>
    <file>formbase.cpp</file>
    <file>formbase.h</file>
    <file>kldatabase.cpp</file>
    <file>kldatabase.h</file>
    <file>kllogger.cpp</file>
    <file>kllogger.h</file>
    <file>klpermission.cpp</file>
    <file>klpermission.h</file>
    <file>klquery.cpp</file>
    <file>klquery.h</file>
    <file>klresultset.cpp</file>
    <file>klresultset.h</file>
    <file>klresultsetinterpreter.cpp</file>
    <file>klresultsetinterpreter.h</file>
    <file>kltable.cpp</file>
    <file>kltable.h</file>
    <file>kludotecaiface.h</file>
    <file>kludotecaiface_skel.cpp</file>
    <file>klxmlreader.cpp</file>
    <file>klxmlreader.h</file>
    <file>ltlistview.cpp</file>
    <file>ltlistview.h</file>
    <file>lttoolbox.cpp</file>
    <file>lttoolbox.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/krawek/Proyectos/kludoteca/src/rents-module/</name>
    <path>/home/krawek/Proyectos/kludoteca/src/rents-module/</path>
    <filename>dir_000006.html</filename>
    <file>formadminrents.cpp</file>
    <file>formadminrents.h</file>
    <file>rentswidget.cpp</file>
    <file>rentswidget.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/krawek/Proyectos/kludoteca/src/</name>
    <path>/home/krawek/Proyectos/kludoteca/src/</path>
    <filename>dir_000001.html</filename>
    <dir>/home/krawek/Proyectos/kludoteca/src/admin-module/</dir>
    <dir>/home/krawek/Proyectos/kludoteca/src/clients-module/</dir>
    <dir>/home/krawek/Proyectos/kludoteca/src/games-module/</dir>
    <dir>/home/krawek/Proyectos/kludoteca/src/lib/</dir>
    <dir>/home/krawek/Proyectos/kludoteca/src/rents-module/</dir>
    <dir>/home/krawek/Proyectos/kludoteca/src/tournament-module/</dir>
    <file>crashhandler.cpp</file>
    <file>crashhandler.h</file>
    <file>klfirstdialog.cpp</file>
    <file>klfirstdialog.h</file>
    <file>kludoteca.cpp</file>
    <file>kludoteca.h</file>
    <file>kludotecaview.cpp</file>
    <file>kludotecaview.h</file>
    <file>ldtapp.cpp</file>
    <file>ldtapp.h</file>
    <file>main.cpp</file>
    <file>osd.cpp</file>
    <file>osd.h</file>
    <file>osd.moc.cpp</file>
    <file>pref.cpp</file>
    <file>pref.h</file>
    <file>validateuser.cpp</file>
    <file>validateuser.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/krawek/Proyectos/kludoteca/src/tournament-module/</name>
    <path>/home/krawek/Proyectos/kludoteca/src/tournament-module/</path>
    <filename>dir_000007.html</filename>
    <file>formmatchorder.cpp</file>
    <file>formmatchorder.h</file>
    <file>formparticipants.cpp</file>
    <file>formparticipants.h</file>
    <file>formquerytournament.cpp</file>
    <file>formquerytournament.h</file>
    <file>formtournament.cpp</file>
    <file>formtournament.h</file>
    <file>matchgenerator.cpp</file>
    <file>matchgenerator.h</file>
    <file>participantslist.cpp</file>
    <file>participantslist.h</file>
    <file>roundlist.cpp</file>
    <file>roundlist.h</file>
    <file>tournamentactive.cpp</file>
    <file>tournamentactive.h</file>
    <file>tournamentmodule.cpp</file>
    <file>tournamentmodule.h</file>
    <file>tournamentold.cpp</file>
    <file>tournamentold.h</file>
    <file>tournamenttabbar.cpp</file>
    <file>tournamenttabbar.h</file>
    <file>tournamentwidget.cpp</file>
    <file>tournamentwidget.h</file>
  </compound>
</tagfile>
