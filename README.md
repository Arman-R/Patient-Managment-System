<h1>Patient Managment System</h1>


<p>This project consists of three parts: <p>

<ol> 
<li> <a href ="#admin-panel">Admin panel  </a> </li>
<li> <a href ="#doctor's-program "> Doctor's program </a> </li>
<li> <a href ="#database"> Database </a> </li>
</ol>


<div id ="admin-panel">

<h3> <b> Admin Panel </b> </h3>
<br>

<img src ="./images/admin_panel.png">


<p>Admin Panel is a part of the system through which MYSQL database can be controlled.
Admin can create doctor's account and also delete it. 
<br>


<p> 



</p>
<img src="./images/registration_acc.png">
To create account admin must input account's details and pass validation rules (name cannot have numbers and symbols, mail format must be valid, etc.)
Before password is stored in database it is encrypted using AES encryption

 </p> 

</div>
<div id ="doctor's-program">

 <h2> <b> Doctor's program </b></h2>

 <p> Doctor must enter valid credentials (email, password) in order to login. 
 
 After successful login, doctor can search for patients that were registered that day. Doctor can use name, last name, doctor's id to make search for patients easier. 


<br>

<img src="./images/reception.png">
<img src = "./images/patients.png">

 If doctor wants to receive patient and register it in daily patients he can search for patients from table that stores registered patients in canton, city, country. 
<br>
 Doctors can use many filters in order to find patient easier. For example, patients's name that starts with "n".
<br>
Doctor can delete received patient by clicking on row where patient is stored and pressing button "Delete".
<br>
SQL queries for filtering can be found in files "patientsinfo.cpp" method "on_filterButton_clicked()" and "patientsreception.cpp" method "on_SearchButton_clicked()".

 </p>

</div>

<div id ="database">
<h2> Database </h2>
 <p> Database has 4 tables:</p>
<ol>
<li> Doctor's accounts </li>
<li>  Doctors</li>

<li> Patients db</li>
<li> Daily patients  </li>
</ol>


<p> Doctor's account table </p>
<img src = "./images/Database/dr_accounts.png">




<p>Doctors</p>
<img src="./images/Database/doctors.png">
<p> 




<p>Patients db</p>
<img src="./images/Database/patientsdb.png"> 

 <p>Daily patients</p>
 <img src ="./images/Database/daily_patients.png">


</div>

