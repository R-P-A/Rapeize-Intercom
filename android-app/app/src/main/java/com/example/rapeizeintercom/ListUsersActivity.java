package com.example.rapeizeintercom;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class ListUsersActivity extends AppCompatActivity {

    TextView usersList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_users);

        /**
         * Receive user data from login
         */
        Bundle bundle = getIntent().getExtras();
        String message = bundle.getString("msgToActivity");

        String[] users = message.split("\n");

        usersList = (TextView) findViewById(R.id.usersList);
        usersList.setVisibility(View.VISIBLE);

        for(int i = 0; i< users.length; i++)
            usersList.setText(users[i] + "\n");
    }
}
