export type Advisory = {
  commodity: string;
  recommendation: "HOLD" | "SELL_NOW" | "HOLD_PARTIAL";
  holdDays: string;
  confidence: number;
  reasons: { factor: string; impact: string; weight: number; direction: "bullish"|"bearish"|"neutral" }[];
  math: { todayPrice: number; forecastPeak: number; peakDate: string; grossGain: number; storageCost: number; transportCost: number; netGain: number; netPct: number };
  risk: { level: "Low"|"Medium"|"High"; brake: string; autoTrigger: string };
  actionWhatsApp: string;
};

export const advisory: Advisory = {
  commodity: "Onion (Red, A-Grade 55-70mm)",
  recommendation: "HOLD",
  holdDays: "10-14 days",
  confidence: 87,
  reasons: [
    { factor: "Arrivals ↓ 18% WoW (420q vs 512q)", impact: "+₹110/q price pressure", weight: 30, direction: "bullish" },
    { factor: "Retail demand ↑ 12% (Ganesh Chaturthi stocking, Nashik/Pune)", impact: "+₹70/q", weight: 22, direction: "bullish" },
    { factor: "IMD: No heavy rain next 10 days (no dump risk)", impact: "HOLD safe", weight: 18, direction: "bullish" },
    { factor: "Buyer bids tight: Sahyadri ₹2950, Export ₹3100 spread +150", impact: "Negotiation leverage", weight: 15, direction: "bullish" },
    { factor: "Storage viable: NAFED Junnar 2km @ ₹45/q/week", impact: "Cost covered in 4 days", weight: 15, direction: "neutral" },
  ],
  math: { todayPrice: 2850, forecastPeak: 3120, peakDate: "31 Aug", grossGain: 270, storageCost: 90, transportCost: 42, netGain: 240, netPct: 8.4 },
  risk: { level: "Medium", brake: "Monsoon revival 28-31 Aug (+25% arrival risk) → model flips to SELL if forecast drops >5% or arrivals rebound >15% WoW", autoTrigger: "Auto WhatsApp/SMS if trigger hits" },
  actionWhatsApp: "🟢 KrishiConnect: Pune Onion ₹2850 → HOLD 12 days till 31 Aug. Peak ₹3120/q (LSTM 87%). Net +₹240/q after ₹90 storage. Reserve NAFED 2km? Reply 1=Hold 2=Sell Now 3=Call FPO [Marathi]"
};

export const advisoryLogic = `IF (arrival_drop >15% AND demand_up >8% AND storage_cost*2 < forecast_gain AND rain_risk==low) THEN HOLD else SELL_NOW. Thresholds tuned on 2023-25 Lasalgaon backtest (MAPE 8.3%).`;
