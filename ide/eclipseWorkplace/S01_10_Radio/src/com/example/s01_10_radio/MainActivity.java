package com.example.s01_10_radio;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.CompoundButton;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;


public class MainActivity extends ActionBarActivity {

	private RadioGroup radioGroup;
	private RadioButton radioButton1;
	private RadioButton radioButton2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        radioGroup =(RadioGroup)findViewById(R.id.RADIOGROUP_ID);
        radioButton1 =(RadioButton)findViewById(R.id.RADIOBUTTON1_ID);
        radioButton2 =(RadioButton)findViewById(R.id.RADIOBUTTON2_ID);

        RadioGroupOnCheckedChangeListener radioOnCheckedChangeListener = new RadioGroupOnCheckedChangeListener();
        radioGroup.setOnCheckedChangeListener(radioOnCheckedChangeListener);
        
        RadioButtonOnCheckedChangeListener radioButtonOnCheckedChangeListener = new RadioButtonOnCheckedChangeListener();
        radioButton1.setOnCheckedChangeListener(radioButtonOnCheckedChangeListener);
        //radioButton2.setOnCheckedChangeListener(radioButtonOnCheckedChangeListener);
    }

    class RadioButtonOnCheckedChangeListener implements android.widget.CompoundButton.OnCheckedChangeListener
    {
    	@Override
    	public void onCheckedChanged(CompoundButton buttonView,
    			boolean isChecked) {
    		// TODO Auto-generated method stub
    		System.out.println("radioButton1" + "is pressed" );
    	}
    }
    
    class RadioGroupOnCheckedChangeListener implements OnCheckedChangeListener
    {
    	@Override
    	public void onCheckedChanged(RadioGroup group, int checkedId) {
    		// TODO Auto-generated method stub
    		RadioGroup radioGroup = (RadioGroup)group;
    		switch(checkedId)
    		{
    		case R.id.RADIOBUTTON1_ID:
    			System.out.println("female");
    			break;
    		case R.id.RADIOBUTTON2_ID:
    			System.out.println("male");
    			break;
    		}
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
