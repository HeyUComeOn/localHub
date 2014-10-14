package com.mitsui011600.s01_16_00_datepicker;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.DatePicker;


public class MainActivity extends ActionBarActivity {

	private Button btn;
	private DatePicker datePicker;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        btn =(Button)findViewById(R.id.BUTTON);
        datePicker=(DatePicker)findViewById(R.id.DATAPICKER);
        
        OnclickListener onclickListener =new OnclickListener();
        btn.setOnClickListener(onclickListener);
    }

    class OnclickListener implements OnClickListener
    {
    	@Override
    	public void onClick(View v) {
    		// TODO Auto-generated method stub
    		int a=datePicker.getYear();
    		int b=datePicker.getMonth();
    		int c=datePicker.getDayOfMonth();
    		System.out.println(a+""+b+c
    		);
    	}
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
