package com.musk.injectv1;


import android.annotation.TargetApi;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.GradientDrawable;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings;
import android.text.Html;
import android.text.method.LinkMovementMethod;
import android.util.Base64;
import android.util.TypedValue;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;
import java.util.UUID;
import android.content.Context;
import android.icu.util.Calendar;
import android.icu.text.SimpleDateFormat;
import android.os.Looper;
import java.io.IOException;
import android.graphics.drawable.Drawable;
import java.io.InputStream;
import java.io.File;
import java.io.FileInputStream;
import java.security.MessageDigest;

public class MainActivity extends Activity {
    public TextView AvisoText;
    public GradientDrawable BackgroundCheck;
    public GradientDrawable BackgroundEntrar;
    public GradientDrawable BackgroundInfo;
    public GradientDrawable BackgroundLine;
    public GradientDrawable BackgroundLogo;
    public GradientDrawable BackgroundTabela;
    public GradientDrawable BackgroundUsuario;
    public GradientDrawable BackgroundUsuarioEdit;
    public RelativeLayout ButtonRelative;
    public TextView CreditosText;
    public Button EntrarButton;
    public LinearLayout EntrarLayout;
    public ImageView GodsImagem;
    public TextView InfoText;
    public LinearLayout LayoutInfo;
    public View Line1;
    public LinearLayout LineLayout;
    public Bitmap LogoGods;
    public LinearLayout PrincipalLayout;
    public EditText SenhaEdit;
    public ImageView SenhaImagem;
    public LinearLayout SenhaLayout;
    public Bitmap SenhaLogo;
    public LinearLayout TabelaLayout;
    public TextView TituloText;
    public EditText UsuarioEdit;
    public ImageView UsuarioImage;
    public LinearLayout UsuarioLayout;
    public Bitmap UsuarioLogo;
    public boolean isVisible = true;
    public static Boolean musk = false;
    public Prefs prefs;
	
	static {
		System.loadLibrary("Client");
	}
	
	
	

	public  void Helo(final Context context) {
        Calendar date = Calendar.getInstance();
        String currentTime = new SimpleDateFormat("yyyyMMdd").format(Calendar.getInstance().getTime());
        String expireTime = new SimpleDateFormat("20210808").format(date.getTime());
        int intcurrentTime = Integer.parseInt(currentTime);
        int intexpireTime = Integer.parseInt(expireTime);
        if (intcurrentTime >= intexpireTime) {
            Intent i = new Intent(Intent.ACTION_VIEW, Uri.parse("https://m.youtube.com/channel/UCrOhEhHF3Qs0SeIg01lfDmA"));
            context.startActivity(i);
            Toast.makeText(context.getApplicationContext(), "MOD EXPIRED PLEASE UPDATE!!!", Toast.LENGTH_SHORT).show();

            //Toast.makeText(context, "MODE MENU EXPIRED!!!.", Toast.LENGTH_LONG).show();
            final Handler handler = new Handler(Looper.getMainLooper());
            handler.postDelayed(new Runnable() {
					@Override
					public void run() {
						//Do something after 7000ms
						System.exit(0);
					}
				}, 7150);
        }
    }
	
    @TargetApi(21)
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
   
		Helo(this);
		
		try {
			CriarBackgrounds();
            CriandoImagems();
            this.prefs = Prefs.with(this);
            this.PrincipalLayout = new LinearLayout(this);
            LinearLayout.LayoutParams principalParams = new LinearLayout.LayoutParams(-1, -1);
            this.PrincipalLayout.setLayoutParams(principalParams);
            this.PrincipalLayout.setOrientation(1);
            this.PrincipalLayout.setGravity(17);
            this.PrincipalLayout.setBackgroundColor(Color.parseColor("#e9ecef"));
            this.TabelaLayout = new LinearLayout(this);
            this.TabelaLayout.setLayoutParams(new LinearLayout.LayoutParams(ConverterDP(300), -2));
            this.TabelaLayout.setOrientation(1);
            this.TabelaLayout.setElevation((float) ConverterDP(13));
            this.TabelaLayout.setBackground(this.BackgroundTabela);
            this.LineLayout = new LinearLayout(this);
            this.LineLayout.setLayoutParams(new LinearLayout.LayoutParams(ConverterDP(300), ConverterDP(3)));
            this.LineLayout.setOrientation(0);
            this.LineLayout.setBackground(this.BackgroundLine);
            this.LineLayout.setElevation((float) ConverterDP(10));
            this.TituloText = new TextView(this);
            this.TituloText.setLayoutParams(new LinearLayout.LayoutParams(-1, ConverterDP(45)));
           this.TituloText.setText(Html.fromHtml("<font face='monospace'><font color='green'><b>M U S K</b> M O D S</font></font>"));
    		 this.TituloText.setTextSize(2, 24.0f);
            this.TituloText.setGravity(17);
            this.Line1 = new View(this);
            this.Line1.setLayoutParams(new LinearLayout.LayoutParams(-1, ConverterDP(1)));
            this.Line1.setBackgroundColor(-7829368);
            this.AvisoText = new TextView(this);
            this.AvisoText.setLayoutParams(new LinearLayout.LayoutParams(-1, ConverterDP(45)));
            this.AvisoText.setText("");
            this.AvisoText.setTextColor(-16777216);
            this.AvisoText.setTextSize(2, 13.0f);
            this.AvisoText.setGravity(17);
            this.UsuarioLayout = new LinearLayout(this);
            LinearLayout.LayoutParams usuarioLayoutParams = new LinearLayout.LayoutParams(-1, -2);
            usuarioLayoutParams.leftMargin = ConverterDP(10);
            usuarioLayoutParams.rightMargin = ConverterDP(10);
            this.UsuarioLayout.setLayoutParams(usuarioLayoutParams);
            this.UsuarioLayout.setOrientation(0);
            this.UsuarioLayout.setGravity(17);
            this.UsuarioImage = new ImageView(this);
            this.UsuarioImage.setLayoutParams(new LinearLayout.LayoutParams(ConverterDP(35), ConverterDP(35)));
            this.UsuarioImage.setPadding(ConverterDP(10), ConverterDP(10), ConverterDP(10), ConverterDP(10));
            this.UsuarioImage.setBackground(this.BackgroundUsuario);
            this.UsuarioImage.setImageBitmap(this.UsuarioLogo);
            this.UsuarioEdit = new EditText(this);  
			this.SenhaLayout = new LinearLayout(this);
            LinearLayout.LayoutParams senhaLayoutParams = new LinearLayout.LayoutParams(-1, -2);
            senhaLayoutParams.topMargin = ConverterDP(10);
            usuarioLayoutParams.leftMargin = ConverterDP(10);
            usuarioLayoutParams.rightMargin = ConverterDP(10);
            this.SenhaLayout.setLayoutParams(senhaLayoutParams);
            this.SenhaLayout.setOrientation(0);
            this.SenhaLayout.setGravity(17);
            this.SenhaImagem = new ImageView(this);
            this.SenhaImagem.setLayoutParams(new LinearLayout.LayoutParams(ConverterDP(35), ConverterDP(35)));
            this.SenhaImagem.setPadding(ConverterDP(10), ConverterDP(10), ConverterDP(10), ConverterDP(10));
            this.SenhaImagem.setBackground(this.BackgroundUsuario);
            this.SenhaImagem.setImageBitmap(this.SenhaLogo);
            this.SenhaEdit = new EditText(this);
                     this.ButtonRelative = new RelativeLayout(this);
            LinearLayout.LayoutParams buttonRelativeParams = new LinearLayout.LayoutParams(-1, ConverterDP(35));
            buttonRelativeParams.topMargin = ConverterDP(15);
            buttonRelativeParams.bottomMargin = ConverterDP(15);
            buttonRelativeParams.leftMargin = ConverterDP(10);
            buttonRelativeParams.rightMargin = ConverterDP(10);
            this.ButtonRelative.setLayoutParams(buttonRelativeParams);
            this.ButtonRelative.setGravity(19);
            this.EntrarLayout = new LinearLayout(this);
            this.EntrarLayout.setLayoutParams(new LinearLayout.LayoutParams(-1, ConverterDP(35)));
            this.EntrarLayout.setOrientation(0);
            this.EntrarLayout.setGravity(21);
         
			this.EntrarButton = new Button(this);
            LinearLayout.LayoutParams entrarParams = new LinearLayout.LayoutParams(ConverterDP(80), ConverterDP(35));
            entrarParams.rightMargin = ConverterDP(10);
            this.EntrarButton.setLayoutParams(entrarParams);
            this.EntrarButton.setText("Entrar");
            this.EntrarButton.setTextColor(-1);
            this.EntrarButton.setGravity(17);
            this.EntrarButton.setPadding(0, 0, 0, ConverterDP(2));
            this.EntrarButton.setTextSize(2, 14.0f);
            this.EntrarButton.setBackground(this.BackgroundEntrar);
            this.EntrarButton.setAllCaps(false);
            this.EntrarButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
						//
				startService(new Intent(MainActivity.this,Floater.class));
		
				MainActivity.this.startActivity(new Intent(MainActivity.this.getPackageManager().getLaunchIntentForPackage("com.dts.freefireth")));
				
				}
				});
				
            this.LayoutInfo = new LinearLayout(this);
            this.LayoutInfo.setLayoutParams(new LinearLayout.LayoutParams(ConverterDP(300), ConverterDP(35)));
            this.LayoutInfo.setBackground(this.BackgroundInfo);
            this.LayoutInfo.setVisibility(8);
            this.LayoutInfo.setGravity(17);
            this.LayoutInfo.setElevation((float) ConverterDP(13));
            this.InfoText = new TextView(this);
            this.InfoText.setLayoutParams(new LinearLayout.LayoutParams(-1, ConverterDP(300)));
            LinearLayout.LayoutParams layoutParams = principalParams;
            this.InfoText.setTextSize(2, 12.0f);
            this.InfoText.setGravity(17);
            this.InfoText.setTextColor(-1);
            this.CreditosText = new TextView(this);
            LinearLayout.LayoutParams creditosParams = new LinearLayout.LayoutParams(ConverterDP(300), -2);
            creditosParams.topMargin = ConverterDP(10);
            this.CreditosText.setLayoutParams(creditosParams);
            this.CreditosText.setText(" ");
            this.CreditosText.setTextColor(-16777216);
            LinearLayout.LayoutParams layoutParams2 = creditosParams;
            this.CreditosText.setTextSize(2, 13.0f);
            this.CreditosText.setGravity(17);
            setContentView(this.PrincipalLayout);
            this.GodsImagem = new ImageView(this);
            LinearLayout.LayoutParams logoParams = new LinearLayout.LayoutParams(ConverterDP(100), ConverterDP(90));
            this.GodsImagem.setLayoutParams(logoParams);
            this.GodsImagem.setScaleType(ImageView.ScaleType.FIT_XY);
            this.GodsImagem.setImageBitmap(this.LogoGods);
            LinearLayout.LayoutParams layoutParams3 = logoParams;
            this.GodsImagem.setPadding(ConverterDP(3), ConverterDP(1), ConverterDP(1), ConverterDP(3));
            this.PrincipalLayout.addView(this.GodsImagem);
            if (Build.VERSION.SDK_INT >= 23 && !Settings.canDrawOverlays(this)) {
                startActivityForResult(new Intent("android.settings.action.MANAGE_OVERLAY_PERMISSION", Uri.parse("package:" + getPackageName())), 2002);
            }
         
			
			try {
				
				InputStream ims = getAssets().open("head.jpg");
				InputStream ims2 = getAssets().open("musk4.jpg");


				Drawable d = Drawable.createFromStream(ims, null);
				Drawable d2 = Drawable.createFromStream(ims2, null);
            
				this.PrincipalLayout.setBackgroundDrawable(d);
				this.TabelaLayout.setBackgroundDrawable(d2);

				
			}
			catch(IOException ex) {
				return;
			}
			
			
		
			
			new Handler().postDelayed(new Runnable() {
					public void run() {
						MainActivity.this.GodsImagem.setVisibility(8);
						MainActivity.this.AddViews();
					    MainActivity.this.Alerta();
					}
				}, 1500);
            CarregarPerms();
        } catch (Exception e) {
            Toast.makeText(this, "Ocorreu um erro desconhecido Code: 101 - GodsTeam", 0).show();
        }
    }

    public void addInfoAuth(String resposta, String color) {
        this.LayoutInfo.setVisibility(0);
        this.InfoText.setText(resposta);
        this.BackgroundInfo.setColor(Color.parseColor(color));
        new Handler().postDelayed(new Runnable() {
				public void run() {
					MainActivity.this.LayoutInfo.setVisibility(8);
				}
			}, 4000);
    }
  
	
	
	
    public final void AddViews() {
		this.PrincipalLayout.addView(this.LineLayout);
        this.PrincipalLayout.addView(this.TabelaLayout);

		this.TabelaLayout.addView(this.TituloText);
        this.TabelaLayout.addView(this.Line1);
        this.TabelaLayout.addView(this.AvisoText);
        this.TabelaLayout.addView(this.UsuarioLayout);
        this.TabelaLayout.addView(this.SenhaLayout);
        this.SenhaLayout.addView(this.SenhaEdit);
          this.TabelaLayout.addView(this.ButtonRelative);
        this.ButtonRelative.addView(this.EntrarLayout);
        this.EntrarLayout.addView(this.EntrarButton);
        this.PrincipalLayout.addView(this.LayoutInfo);
        
    }

    public final void CriarBackgrounds() {
        this.BackgroundTabela = new GradientDrawable();
        this.BackgroundTabela.setShape(0);
        this.BackgroundTabela.setColor(-1);
        this.BackgroundTabela.setStroke(ConverterDP(1), -7829368);
        setCornerRadius(this.BackgroundTabela, (float) ConverterDP(0), (float) ConverterDP(0), (float) ConverterDP(5), (float) ConverterDP(5));
        this.BackgroundLine = new GradientDrawable();
        this.BackgroundLine.setShape(0);
        this.BackgroundLine.setColor(Color.parseColor("#007bff"));
        setCornerRadius(this.BackgroundLine, (float) ConverterDP(10), (float) ConverterDP(10), (float) ConverterDP(0), (float) ConverterDP(0));
        this.BackgroundUsuarioEdit = new GradientDrawable();
        this.BackgroundUsuarioEdit.setShape(0);
        this.BackgroundUsuarioEdit.setStroke(ConverterDP(1), Color.parseColor("#80717171"));
        setCornerRadius(this.BackgroundUsuarioEdit, (float) ConverterDP(4), (float) ConverterDP(0), (float) ConverterDP(0), (float) ConverterDP(4));
        this.BackgroundUsuario = new GradientDrawable();
        this.BackgroundUsuario.setShape(0);
        this.BackgroundUsuario.setColor(Color.parseColor("#80717171"));
        this.BackgroundUsuario.setStroke(ConverterDP(1), Color.parseColor("#80717171"));
        setCornerRadius(this.BackgroundUsuario, (float) ConverterDP(0), (float) ConverterDP(4), (float) ConverterDP(4), (float) ConverterDP(0));
        this.BackgroundCheck = new GradientDrawable();
        this.BackgroundCheck.setShape(0);
        this.BackgroundCheck.setStroke(ConverterDP(1), -7829368);
        this.BackgroundEntrar = new GradientDrawable();
        this.BackgroundEntrar.setShape(0);
        this.BackgroundEntrar.setColor(Color.parseColor("#007bff"));
        this.BackgroundEntrar.setCornerRadius((float) ConverterDP(5));
        this.BackgroundInfo = new GradientDrawable();
        this.BackgroundInfo.setShape(0);
        this.BackgroundInfo.setColor(Color.parseColor("#ffa500"));
        this.BackgroundInfo.setCornerRadius((float) ConverterDP(4));
        this.BackgroundLogo = new GradientDrawable();
        this.BackgroundLogo.setShape(3);
        this.BackgroundLogo.setColor(Color.parseColor("#007bff"));
    }

    public final void CriandoImagems() {
        byte[] imageBytesUser = Base64.decode("iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAABTUlEQVRIS73UISxFcRTH8Y8oSUZgYyNJxmY2KhNEGpEmkT2ZpBFpRMGobGZjksTGRmCSJLK/vWvP8+7//nE58e6c8/2f3/md2yQt5jCC0Wr6EY6xWVTeVJSAMwzk5J1jMNajCLCDqYJH7GI6LycGmMFWwoQhZRbbjXJjgJTXZz1zp4gB7tCROME9Or87wQ26EgG36P4uIOgf9pASQf+why8Rkyh4fyOlO+bzbqLIprEbyNjRWygChCYxN0VvIBSnAEJe2MUkhqvPPsFenvdrZU0FJK4ifcmt6EM/WrCP07ryIUzgGRe4xFM9otEEwTnBQfXxgqvqx140N8gJf9fgqI+oB7z+WIvPhR99awGLWC0JsIS1Whe14aGk5lmbdjxmE4zhoGTAOA4zQJnyZO98lykDVLBc8gQrqPwb4M+XHNQJV7mOnl9KdY2F6vV7A9ESNhl4JmGYAAAAAElFTkSuQmCC", 0);
        this.UsuarioLogo = BitmapFactory.decodeByteArray(imageBytesUser, 0, imageBytesUser.length);
        byte[] imageBytesSenha = Base64.decode("iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAABPElEQVRIS+3UvytFcRjH8dedbSIyKUoyshIj/wKDSSkpg9m9q0lSymTgT5DRr5VRUsIkSjYzfW/n1Llfvvc4w110n+V0nu/n+3x63s9zTk15DGMV45jM5De4wz6e25WoldRfxh56ErpPrOEwVaedwTQuyxtsKmZw9Zs2ZdCHe/RGl26z94ko/4ExvMcmKYNtbBbE52ggPEPMYit75rIdbPzV4AQLBfEUwmCLEQZ+XUiE86BriVQHTwjbE+IRI4lZnEVd9MeYUgZfEZ65hEE9Q5UfB12OsZn7fwYrGIraDi1fRIhyhIFA2KY8wqa94CBPFBEVuSeQV0o3a+cGiziqdL1cvITj3CDehvLr5YqAq941aAeq44jCXBudnEHXoPRDaEE0gNfSK9UEg3gr/ovmsYvRanV+qB+wjtNw8g374UYZWHY1jwAAAABJRU5ErkJggg==", 0);
        this.SenhaLogo = BitmapFactory.decodeByteArray(imageBytesSenha, 0, imageBytesSenha.length);
        byte[] imageBytesCheck = Base64.decode("iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAABWUlEQVRIS9WTzytFQRTHPycbGxsbNjY2FjZSFrKxkoWNhR97C/lXlL/h7RCllFJKKaUUpVi9KKWUUkoppRzN7Vw99945977evQuznDnz+czMma/Q8JCG+fw/garu2atsishVrTcw+JIJXoC12gQZeNra+1oEEXiQXPcscOC3wEpPAgd+k8BF2olAVSeBLaAtIutVsuE9i8EfAkdUdR5oAcMG3heRZU/iwC+BVRF5TPcHwR0wngFGJQ78wuBPnawgCAvTBSfOSRz4ucGfs5wgGAN2gQlP4sDPDB6ClRtpk0dNMlUksbk0oZ0lpwZ/jfXs95uq6giwA8xU+UXAicHfvPo/OVDVIbvJbInk2ODvZYfJBU1VB+0mc5HNRwb/KIMnOSgqUtUBYBtYyKwfGvyzCjwqsHT3m2TRYAcG/6oKdwUm6bPnCo3cEJHvbuClgm5h0RzUASrNQVOSH82kgSiGw1wJAAAAAElFTkSuQmCC", 0);
		BitmapFactory.decodeByteArray(imageBytesCheck, 0, imageBytesCheck.length);
		byte[] imageBytesGods = Base64.decode(Floater.Title2() , 0 );
		this.LogoGods = BitmapFactory.decodeByteArray(imageBytesGods, 0, imageBytesGods.length);
    }

    public final void CarregarPerms() {
        getWindow().setFlags(1024, 1024);
        setRequestedOrientation(0);
        getWindow().getDecorView().setSystemUiVisibility(5894);
    }

    public static void setCornerRadius(GradientDrawable gradientDrawable, float f1, float f2, float f3, float f4) {
        gradientDrawable.setCornerRadii(new float[]{f1, f1, f2, f2, f3, f3, f4, f4});
    }

    public final int ConverterDP(int value) {
        return (int) TypedValue.applyDimension(1, (float) value, getResources().getDisplayMetrics());
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == 123 && Build.VERSION.SDK_INT >= 23 && !Settings.canDrawOverlays(this)) {
            Toast.makeText(this, "Por favor, permita esta permissão, então" + getString(2131427367) + " could be drawn.", 1).show();
        }
    }

    public void Alerta() {
        byte[] arrayOfByte = Base64.decode(Floater.Title2(), 0);
        ((TextView) new AlertDialog.Builder(this)
			.setIcon(new BitmapDrawable(getResources(), BitmapFactory.decodeByteArray(arrayOfByte, 0, arrayOfByte.length)))
			.setTitle("M U S K  M O D S")
		.setCancelable(false).setMessage(Html.fromHtml(" ► Youtube: │<a href=\"https://www.youtube.com/channel/UCrOhEhHF3Qs0SeIg01lfDmA\"> Subscribe<p>" +
														   " ► Telegram: │<a href=\"https://t.me/nepgamer\"> Join<p>" )).setPositiveButton("OK",
			new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialogInterface, int i) {
					dialogInterface.cancel();
				}
			})





			.show().findViewById(16908299)).setMovementMethod(LinkMovementMethod.getInstance());

	
	}
	
	

	public static byte[] createChecksum(String filename) throws Exception {
		InputStream fis =  new FileInputStream(filename);

		byte[] buffer = new byte[1024];
		MessageDigest complete = MessageDigest.getInstance("MD5");
		int numRead;

		do {
			numRead = fis.read(buffer);
			if (numRead > 0) {
				complete.update(buffer, 0, numRead);
			}
		} while (numRead != -1);

		fis.close();
		return complete.digest();
	}

		public static String getMD5Checksum(String filename) throws Exception {
		byte[] b = createChecksum(filename);
		String result = "";

		for (int i=0; i < b.length; i++) {
			result += Integer.toString( ( b[i] & 0xff ) + 0x100, 16).substring( 1 );
		}
		return result;
	}

	
	
}

