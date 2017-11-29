package com.example.rapeizeintercom;

import android.annotation.TargetApi;
import android.os.AsyncTask;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class AdminCreateUserActivity extends AppCompatActivity {

    Button buttonAdminCreate;
    String userID, password;
    EditText createUserID, createUserPassword, createUserIsAdmin, createUserName, createUserPhone, createUserEmail,
             createUserBeginWeekDay, createUserEndWeekDay, createUserBeginTime, createUserEndTime;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_admin_create_user);

        /**
         * Receive user data from login
         */
        Bundle bundle = getIntent().getExtras();
        String message = bundle.getString("msgToActivity");

        String[] user = message.split(",");
        userID = user[0];
        password = user[1];

        createUserID = (EditText) findViewById(R.id.createUserID);
        createUserPassword = (EditText) findViewById(R.id.createUserPassword);
        createUserIsAdmin = (EditText) findViewById(R.id.createUserIsAdmin);
        createUserName = (EditText) findViewById(R.id.createUserName);
        createUserPhone = (EditText) findViewById(R.id.createUserPhone);
        createUserEmail = (EditText) findViewById(R.id.createUserEmail);
        createUserBeginWeekDay = (EditText) findViewById(R.id.createUserBeginWeekDay);
        createUserEndWeekDay = (EditText) findViewById(R.id.createUserEndWeekDay);
        createUserBeginTime = (EditText) findViewById(R.id.createUserBeginTime);
        createUserEndTime = (EditText) findViewById(R.id.createUserEndTime);

        // Locate the buttonCheckOut in activity_user.xml
        buttonAdminCreate = (Button) findViewById(R.id.buttonCreateUser);

        buttonAdminCreate.setOnClickListener(buttonCreateOnClickListener);
    }

    View.OnClickListener buttonCreateOnClickListener = new View.OnClickListener() {

        @TargetApi(Build.VERSION_CODES.HONEYCOMB) @Override
        public void onClick(View arg0) {
            String tMsg = "createUser," + userID + "," + password;

            String createUserIDTemp, createUserPasswordTemp, createUserIsAdminTemp, createUserNameTemp, createUserPhoneTemp, createUserEmailTemp,
                   createUserBeginWeekDayTemp, createUserEndWeekDayTemp, createUserBeginTimeTemp, createUserEndTimeTemp;
            String createUserData;

            createUserIDTemp = createUserID.getText().toString();
            createUserPasswordTemp = createUserPassword.getText().toString();
            createUserIsAdminTemp = createUserIsAdmin.getText().toString();
            createUserNameTemp = createUserName.getText().toString();
            createUserPhoneTemp = createUserPhone.getText().toString();
            createUserEmailTemp = createUserEmail.getText().toString();
            createUserBeginWeekDayTemp = createUserBeginWeekDay.getText().toString();
            createUserEndWeekDayTemp = createUserEndWeekDay.getText().toString();
            createUserBeginTimeTemp = createUserBeginTime.getText().toString();
            createUserEndTimeTemp = createUserEndTime.getText().toString();

            createUserData = createUserIDTemp           + "," + createUserPasswordTemp   + "," +
                             createUserIsAdminTemp      + "," + createUserNameTemp       + "," +
                             createUserPhoneTemp        + "," + createUserEmailTemp      + "," +
                             createUserBeginWeekDayTemp + "," + createUserEndWeekDayTemp + "," +
                             createUserBeginTimeTemp    + "," + createUserEndTimeTemp;

            tMsg += "," + createUserData;

            MyClientTask myClientTask = new MyClientTask(tMsg);

            /**
             * Execute socket
             */
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB)
                myClientTask.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
            else
                myClientTask.execute();

            /**
             * Wait for server response
             */
            while (!myClientTask.getReadDone());
            myClientTask.setReadDone(false);

            /**
             * Handle the sign out
             */
            if (myClientTask.getResponse().equals("Checked-out with success")) {
                Toast.makeText(getApplicationContext(), myClientTask.getResponse(), Toast.LENGTH_SHORT).show();
            } else {
                Toast.makeText(getApplicationContext(), myClientTask.getResponse(), Toast.LENGTH_SHORT).show();
            }
        }
    };
}
