package com.mitsui0202.s02_02_lifecycle;



import android.support.v7.app.ActionBarActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;


public class MainActivity extends ActionBarActivity {

	private Button btn;
	//��Activity��һ�α�����ʱ����
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.activity_main);
        
        btn=(Button)findViewById(R.id.button1);
        
        
        OnclickListener onclickLisener =new OnclickListener();
        btn.setOnClickListener(onclickLisener);
        
        System.out.println("xxx___MainActivity onCreate !-->��Activity��һ�α�����ʱ");
        
        
    }
    
    //��Activity��ÿɼ�ʱ�����������
    @Override
	protected void onStart() {
		// TODO Auto-generated method stub
		super.onStart();
        System.out.println("xxx___MainActivity onStart !-->��Activity��ÿɼ�ʱ");

	}

    //��Activity׼�����û�����ʱ�����������
    @Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
        System.out.println("xxx___MainActivity onResume !-->��Activity׼�����û�����ʱ");

	}

    //��ϵͳ����������һ��Activityʱ�����������
	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
        System.out.println("xxx___MainActivity onPause !-->��ϵͳ����������һ��Activityʱ");

	}

	//��ǰActivity��ò��ɼ�ʱ�����������
	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		super.onStop();
        System.out.println("xxx___MainActivity onStop !-->��ǰActivity��ò��ɼ�ʱ");

	}

	//��ǰActivity������֮ǰ�����������
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
        System.out.println("xxx___MainActivity onDestroy !-->��ǰActivity������֮ǰ");

	}
	
	//�����Activity�ٴ�����֮ǰ�����������
	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		super.onRestart();
        System.out.println("xxx___MainActivity onRestart !-->���Activity�ٴ�����");

	}

	@Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

	
	 class OnclickListener implements OnClickListener
	    {
	    	@Override
	    	public void onClick(View v) {
	    		// TODO Auto-generated method stub
	    		Intent intent =new Intent();
	    		
	    		//intent.setClass(packageContext, cls)
	    		//����һ��Context�࣬Activity��Context�������
	    		//��һ��������дthis����Ϊ������OnclickListener�Ķ���
	    		intent.setClass(MainActivity.this, OtherActivity.class);
	    		startActivity(intent);
	    	}
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