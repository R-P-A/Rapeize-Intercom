package com.example.rapeizeintercom;

import android.annotation.TargetApi;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class AdminDeleteUserActivity extends AppCompatActivity {

    Button buttonAdminDeleteUser;
    EditText deleteUserID;
    String userID, password;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_admin_delete_user);

        /**
         * Receive user data from login
         */
        Bundle bundle = getIntent().getExtras();
        String message = bundle.getString("msgToActivity");

        String[] user = message.split(",");
        userID = user[0];
        password = user[1];

        deleteUserID = (EditText) findViewById(R.id.deleteUserID);

        // Locate the buttonDeleteUser in activity_admin_delete_user.xml
        buttonAdminDeleteUser = (Button) findViewById(R.id.buttonDeleteUser);

        buttonAdminDeleteUser.setOnClickListener(buttonDeleteOnClickListener);
    }

    View.OnClickListener buttonDeleteOnClickListener = new View.OnClickListener() {

        @TargetApi(Build.VERSION_CODES.HONEYCOMB) @Override
        public void onClick(View arg0) {
            String tMsg = "deleteUser," + userID + "," + password;

            String deleteUserIDTemp = deleteUserID.getText().toString();

            tMsg += "," + deleteUserIDTemp;

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
            if (myClientTask.getResponse().equals("Checked-out with success"))
                Toast.makeText(getApplicationContext(), myClientTask.getResponse(), Toast.LENGTH_SHORT).show();
            else
                Toast.makeText(getApplicationContext(), myClientTask.getResponse(), Toast.LENGTH_SHORT).show();
        }
    };
}
