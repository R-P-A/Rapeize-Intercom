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

public class AdminUpdateUserActivity extends AppCompatActivity {

    Button buttonAdminUpdate;
    String userID, password;
    EditText updateUserID, updateUserPassword, updateUserIsAdmin, updateUserName, updateUserPhone, updateUserEmail,
            updateUserBeginWeekDay, updateUserEndWeekDay, updateUserBeginTime, updateUserEndTime;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_admin_update_user);

        /**
         * Receive user data from login
         */
        Bundle bundle = getIntent().getExtras();
        String message = bundle.getString("msgToActivity");

        String[] user = message.split(",");
        userID = user[0];
        password = user[1];

        updateUserID = (EditText) findViewById(R.id.updateUserID);
        updateUserPassword = (EditText) findViewById(R.id.updateUserPassword);
        updateUserIsAdmin = (EditText) findViewById(R.id.updateUserIsAdmin);
        updateUserName = (EditText) findViewById(R.id.updateUserName);
        updateUserPhone = (EditText) findViewById(R.id.updateUserPhone);
        updateUserEmail = (EditText) findViewById(R.id.updateUserEmail);
        updateUserBeginWeekDay = (EditText) findViewById(R.id.updateUserBeginWeekDay);
        updateUserEndWeekDay = (EditText) findViewById(R.id.updateUserEndWeekDay);
        updateUserBeginTime = (EditText) findViewById(R.id.updateUserBeginTime);
        updateUserEndTime = (EditText) findViewById(R.id.updateUserEndTime);

        // Locate the buttonCheckOut in activity_user.xml
        buttonAdminUpdate = (Button) findViewById(R.id.buttonUpdateUser);

        buttonAdminUpdate.setOnClickListener(buttonUpdateOnClickListener);
    }

    View.OnClickListener buttonUpdateOnClickListener = new View.OnClickListener() {

        @TargetApi(Build.VERSION_CODES.HONEYCOMB) @Override
        public void onClick(View arg0) {
            String tMsg = "updateUser," + userID + "," + password;

            String updateUserIDTemp, updateUserPasswordTemp, updateUserIsAdminTemp, updateUserNameTemp, updateUserPhoneTemp, updateUserEmailTemp,
                    updateUserBeginWeekDayTemp, updateUserEndWeekDayTemp, updateUserBeginTimeTemp, updateUserEndTimeTemp;
            String updateUserData;

            updateUserIDTemp = updateUserID.getText().toString();
            updateUserPasswordTemp = updateUserPassword.getText().toString();
            updateUserIsAdminTemp = updateUserIsAdmin.getText().toString();
            updateUserNameTemp = updateUserName.getText().toString();
            updateUserPhoneTemp = updateUserPhone.getText().toString();
            updateUserEmailTemp = updateUserEmail.getText().toString();
            updateUserBeginWeekDayTemp = updateUserBeginWeekDay.getText().toString();
            updateUserEndWeekDayTemp = updateUserEndWeekDay.getText().toString();
            updateUserBeginTimeTemp = updateUserBeginTime.getText().toString();
            updateUserEndTimeTemp = updateUserEndTime.getText().toString();

            updateUserData = updateUserIDTemp           + "," + updateUserPasswordTemp   + "," +
                    updateUserIsAdminTemp      + "," + updateUserNameTemp       + "," +
                    updateUserPhoneTemp        + "," + updateUserEmailTemp      + "," +
                    updateUserBeginWeekDayTemp + "," + updateUserEndWeekDayTemp + "," +
                    updateUserBeginTimeTemp    + "," + updateUserEndTimeTemp;

            tMsg += "," + updateUserData;

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
