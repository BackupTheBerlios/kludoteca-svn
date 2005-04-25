<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>
<tagfile>
  <compound kind="class">
    <name>AdminDatabase</name>
    <filename>classAdminDatabase.html</filename>
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
    <name>BDConnection</name>
    <filename>classBDConnection.html</filename>
    <member kind="function">
      <type></type>
      <name>BDConnection</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~BDConnection</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>loadDB</name>
      <anchor>a2</anchor>
      <arglist>(const QString bddriver, const QString bdname, const QString bduser, const QString bdpassword, const QString bdhost)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>loadDB</name>
      <anchor>a3</anchor>
      <arglist>(const QString bduser, const QString bdpassword, const QString bdhost)</arglist>
    </member>
    <member kind="function">
      <type>QSqlDatabase *</type>
      <name>getDB</name>
      <anchor>a4</anchor>
      <arglist>(const QString &amp;key, bool open=false) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>openConnection</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QSqlQuery</type>
      <name>query</name>
      <anchor>a6</anchor>
      <arglist>(const QString &amp;consult=QString::null) const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>dbName</name>
      <anchor>a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>userName</name>
      <anchor>a8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>passwd</name>
      <anchor>a9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>host</name>
      <anchor>a10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDatabaseName</name>
      <anchor>a11</anchor>
      <arglist>(const QString &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setUserName</name>
      <anchor>a12</anchor>
      <arglist>(const QString &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPassword</name>
      <anchor>a13</anchor>
      <arglist>(const QString &amp;password)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setHostName</name>
      <anchor>a14</anchor>
      <arglist>(const QString &amp;host)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BDConnection *</type>
      <name>instance</name>
      <anchor>e0</anchor>
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
    <member kind="function">
      <type></type>
      <name>FormAdminClients</name>
      <anchor>a0</anchor>
      <arglist>(KLDatabase *db, QWidget *parent=0)</arglist>
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
    <member kind="function">
      <type></type>
      <name>FormAdminGame</name>
      <anchor>a0</anchor>
      <arglist>(KLDatabase *db, QWidget *parent=0, const char *name=0)</arglist>
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
      <type>QString</type>
      <name>getGameName</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getDescriptionGame</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getRulesGame</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getTypeGame</name>
      <anchor>a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getReferenceGame</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getTimeUnit</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMinPlayers</name>
      <anchor>a9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getMaxPlayers</name>
      <anchor>a10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getCostUnitTime</name>
      <anchor>a11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getCostTimeAdditional</name>
      <anchor>a12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGameName</name>
      <anchor>a13</anchor>
      <arglist>(const QString &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDescriptionGame</name>
      <anchor>a14</anchor>
      <arglist>(const QString &amp;description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRulesGame</name>
      <anchor>a15</anchor>
      <arglist>(const QString &amp;rules)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTypeGame</name>
      <anchor>a16</anchor>
      <arglist>(const QString &amp;type, int index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setReferenceGame</name>
      <anchor>a17</anchor>
      <arglist>(const QString &amp;reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTimeUnit</name>
      <anchor>a18</anchor>
      <arglist>(const QString &amp;unitTime, int index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMinPlayers</name>
      <anchor>a19</anchor>
      <arglist>(const int &amp;numMinPlayers)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMaxPlayers</name>
      <anchor>a20</anchor>
      <arglist>(const int &amp;numMaxPlayers)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCostUnitTime</name>
      <anchor>a21</anchor>
      <arglist>(const double &amp;costTime)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCostTimeAdditional</name>
      <anchor>a22</anchor>
      <arglist>(const double &amp;costAditional)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QGridLayout *</type>
      <name>m_grid</name>
      <anchor>p0</anchor>
      <arglist></arglist>
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
    <member kind="function">
      <type></type>
      <name>FormAdminUsers</name>
      <anchor>a0</anchor>
      <arglist>(KLDatabase *db, QWidget *parent=0)</arglist>
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
      <name>getSex</name>
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
      <name>setSex</name>
      <anchor>a18</anchor>
      <arglist>(const QString &amp;sex)</arglist>
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
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>cancel</name>
      <anchor>i1</anchor>
      <arglist>()=0</arglist>
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
      <arglist>(Button button1=NoButton, Button button2=NoButton, QWidget *parent=0, const char *name=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FormBase</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTitle</name>
      <anchor>a3</anchor>
      <arglist>(QString newTitle)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setType</name>
      <anchor>a4</anchor>
      <arglist>(Type t)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getType</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTitleFont</name>
      <anchor>a6</anchor>
      <arglist>(QString font, int fontsize)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setExplanation</name>
      <anchor>a7</anchor>
      <arglist>(QString newExplanation)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setupForm</name>
      <anchor>a8</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setupButtons</name>
      <anchor>a9</anchor>
      <arglist>(Button button1, Button button2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTextAcceptButton</name>
      <anchor>a10</anchor>
      <arglist>(QString newText)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTextCancelButton</name>
      <anchor>a11</anchor>
      <arglist>(QString newText)</arglist>
    </member>
    <member kind="function">
      <type>QWidget *</type>
      <name>setupLineEdit</name>
      <anchor>a12</anchor>
      <arglist>(QWidget *parent, QString text, int lineEditWidth=200)</arglist>
    </member>
    <member kind="function">
      <type>HashLineEdit</type>
      <name>setupGridLineEdit</name>
      <anchor>a13</anchor>
      <arglist>(QWidget *parent, QStringList texts, int lineEditWidth=200)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addLineEdits</name>
      <anchor>a14</anchor>
      <arglist>(QWidget *parent, QStringList texts, HashLineEdit &amp;hle, int lineEditWidth)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>lastQueryWasGood</name>
      <anchor>a15</anchor>
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
    <member kind="function">
      <type></type>
      <name>FormTournament</name>
      <anchor>a0</anchor>
      <arglist>(KLDatabase *db, QWidget *parent=0)</arglist>
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
      <name>fillField</name>
      <anchor>a3</anchor>
      <arglist>(QString nameTournament, QString nameGame, double inscription, double discount)</arglist>
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
      <name>cancel</name>
      <anchor>i2</anchor>
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
    <member kind="function">
      <type>int</type>
      <name>getType</name>
      <anchor>a2</anchor>
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
  </compound>
  <compound kind="class">
    <name>KLSelect</name>
    <filename>classKLSelect.html</filename>
    <base>KLQuery</base>
    <member kind="function">
      <type></type>
      <name>KLSelect</name>
      <anchor>a0</anchor>
      <arglist>(QStringList fields, QStringList tables)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KLSelect</name>
      <anchor>a1</anchor>
      <arglist>(QStringList fields, const QString &amp;table)</arglist>
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
      <type>void</type>
      <name>setWhere</name>
      <anchor>a4</anchor>
      <arglist>(QString cwhere)</arglist>
    </member>
    <member kind="function">
      <type>QStringList</type>
      <name>getFields</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getQuery</name>
      <anchor>a6</anchor>
      <arglist>() const </arglist>
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
      <arglist>(const QString &amp;caption, KLDatabase *db=0, QWidget *parentWidget=0L, const char *name=0L, WFlags f=0)</arglist>
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
    <member kind="function">
      <type>QString</type>
      <name>getQuery</name>
      <anchor>a2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setWhere</name>
      <anchor>a3</anchor>
      <arglist>(QString cwhere)</arglist>
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
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>getClickedItem</name>
      <anchor>i0</anchor>
      <arglist>(QListViewItem *item)=0</arglist>
    </member>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>addButtonClicked</name>
      <anchor>i1</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>delButtonClicked</name>
      <anchor>i2</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>modifyButtonClicked</name>
      <anchor>i3</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>queryButtonClicked</name>
      <anchor>i4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>putItems</name>
      <anchor>i5</anchor>
      <arglist>(QStringList items)</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>addItem</name>
      <anchor>i6</anchor>
      <arglist>(const QString &amp;pkey)</arglist>
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
      <type>KListView *</type>
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
      <type>QXmlSimpleReader</type>
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
  </compound>
  <compound kind="class">
    <name>ValidateUser</name>
    <filename>classValidateUser.html</filename>
    <member kind="function">
      <type></type>
      <name>ValidateUser</name>
      <anchor>a0</anchor>
      <arglist>(KLDatabase *db, QWidget *parent=0, const char *name=0)</arglist>
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
    <member kind="function">
      <type>void</type>
      <name>string2perms</name>
      <anchor>a4</anchor>
      <arglist>(const QString &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>activeAdminModule</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>activeRentsModule</name>
      <anchor>a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>activeTournamentModule</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>activeClientsModule</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>activeGamesModule</name>
      <anchor>a9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>/tmp/dcuadra/kludoteca/src/admin-module/</name>
    <path>/tmp/dcuadra/kludoteca/src/admin-module/</path>
    <filename>dir_000004.html</filename>
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
    <name>/tmp/dcuadra/kludoteca/src/clients-module/</name>
    <path>/tmp/dcuadra/kludoteca/src/clients-module/</path>
    <filename>dir_000006.html</filename>
    <file>clientswidget.cpp</file>
    <file>clientswidget.h</file>
    <file>formadminclients.cpp</file>
    <file>formadminclients.h</file>
  </compound>
  <compound kind="dir">
    <name>/tmp/dcuadra/</name>
    <path>/tmp/dcuadra/</path>
    <filename>dir_000001.html</filename>
    <dir>/tmp/dcuadra/kludoteca/</dir>
  </compound>
  <compound kind="dir">
    <name>/tmp/dcuadra/kludoteca/src/games-module/</name>
    <path>/tmp/dcuadra/kludoteca/src/games-module/</path>
    <filename>dir_000007.html</filename>
    <file>formadmingame.cpp</file>
    <file>formadmingame.h</file>
    <file>gameslist.cpp</file>
    <file>gameslist.h</file>
    <file>gamesmodule.cpp</file>
    <file>gamesmodule.h</file>
  </compound>
  <compound kind="dir">
    <name>/tmp/dcuadra/kludoteca/</name>
    <path>/tmp/dcuadra/kludoteca/</path>
    <filename>dir_000002.html</filename>
    <dir>/tmp/dcuadra/kludoteca/src/</dir>
    <file>config.h</file>
  </compound>
  <compound kind="dir">
    <name>/tmp/dcuadra/kludoteca/src/lib/</name>
    <path>/tmp/dcuadra/kludoteca/src/lib/</path>
    <filename>dir_000005.html</filename>
    <file>bdconnection.cpp</file>
    <file>bdconnection.h</file>
    <file>formbase.cpp</file>
    <file>formbase.h</file>
    <file>kldatabase.cpp</file>
    <file>kldatabase.h</file>
    <file>klquery.cpp</file>
    <file>klquery.h</file>
    <file>klresultset.cpp</file>
    <file>klresultset.h</file>
    <file>klresultsetinterpreter.cpp</file>
    <file>klresultsetinterpreter.h</file>
    <file>kludotecaiface.h</file>
    <file>kludotecaiface_skel.cpp</file>
    <file>ltlistview.cpp</file>
    <file>ltlistview.h</file>
    <file>lttoolbox.cpp</file>
    <file>lttoolbox.h</file>
  </compound>
  <compound kind="dir">
    <name>/tmp/dcuadra/kludoteca/src/rents-module/</name>
    <path>/tmp/dcuadra/kludoteca/src/rents-module/</path>
    <filename>dir_000009.html</filename>
    <file>rentswidget.cpp</file>
    <file>rentswidget.h</file>
  </compound>
  <compound kind="dir">
    <name>/tmp/dcuadra/kludoteca/src/</name>
    <path>/tmp/dcuadra/kludoteca/src/</path>
    <filename>dir_000003.html</filename>
    <dir>/tmp/dcuadra/kludoteca/src/admin-module/</dir>
    <dir>/tmp/dcuadra/kludoteca/src/clients-module/</dir>
    <dir>/tmp/dcuadra/kludoteca/src/games-module/</dir>
    <dir>/tmp/dcuadra/kludoteca/src/lib/</dir>
    <dir>/tmp/dcuadra/kludoteca/src/rents-module/</dir>
    <dir>/tmp/dcuadra/kludoteca/src/tournament-module/</dir>
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
    <name>/tmp/</name>
    <path>/tmp/</path>
    <filename>dir_000000.html</filename>
    <dir>/tmp/dcuadra/</dir>
  </compound>
  <compound kind="dir">
    <name>/tmp/dcuadra/kludoteca/src/tournament-module/</name>
    <path>/tmp/dcuadra/kludoteca/src/tournament-module/</path>
    <filename>dir_000008.html</filename>
    <file>formtournament.cpp</file>
    <file>formtournament.h</file>
    <file>tournamentactive.cpp</file>
    <file>tournamentactive.h</file>
    <file>tournamentmodule.cpp</file>
    <file>tournamentmodule.h</file>
    <file>tournamentold.cpp</file>
    <file>tournamentold.h</file>
    <file>tournamentwidget.cpp</file>
    <file>tournamentwidget.h</file>
  </compound>
</tagfile>
