package com.example.rapeizeintercom;

import android.annotation.TargetApi;
import android.os.AsyncTask;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class AdminReadUserActivity extends AppCompatActivity {

    Button buttonAdminReadUser;
    EditText readUserID;
    TextView userRead;
    String userID, password;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_admin_read_user);

        /**
         * Receive user data from login
         */
        Bundle bundle = getIntent().getExtras();
        String message = bundle.getString("msgToActivity");

        String[] user = message.split(",");
        userID = user[0];
        password = user[1];

        buttonAdminReadUser = (Button) findViewById(R.id.buttonReadUser);

        readUserID = (EditText) findViewById(R.id.readUserID);
        userRead = (TextView) findViewById(R.id.userRead);

        buttonAdminReadUser.setOnClickListener(buttonReadOnClickListener);
    }

    View.OnClickListener buttonReadOnClickListener = new View.OnClickListener() {

        @TargetApi(Build.VERSION_CODES.HONEYCOMB) @Override
        public void onClick(View arg0) {
            String tMsg = "readUser," + userID + "," + password;

            String readUserIDTemp = readUserID.getText().toString();

            tMsg += "," + readUserIDTemp;

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
             * Handle the server response
             */
            userRead.setVisibility(View.VISIBLE);
            userRead.setText(myClientTask.getResponse());
        }
    };
}
