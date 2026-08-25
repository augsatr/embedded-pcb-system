export type AlertChannel = "WhatsApp"|"SMS"|"IVR";
export type AlertLog = { id: string; channel: AlertChannel; to: string; template: string; status: "Delivered"|"Read"|"Replied"|"Failed"; time: string; lang: string; };

export const alertTemplates: Record<string, string> = {
  hold: "KrishiConnect: {{commodity}} {{price}} → HOLD {{days}} till {{peakDate}}. Peak {{peak}} ({{conf}}%). Net +{{net}}/q after storage. Reply 1=Reserve {{warehouse}} 2=Sell Now",
  sell: "Alert: {{commodity}} now {{price}} — SELL window open. Buyer {{buyer}} ₹{{offer}}/q needs {{qty}}q. Offer expires 24h.",
  priceAlert: "Price alert: {{commodity}} crossed ₹{{threshold}}/q at {{market}} (now {{price}}). Your lot {{lotId}} gains +₹{{gain}}/q.",
  grievance: "Update: Grievance {{id}} → {{status}}. Officer {{officer}} will call in 24h. Pending ₹{{amount}}."
};

export const alertLogs: AlertLog[] = [
  { id:"W-4821", channel:"WhatsApp", to:"+91 9xxxx x110 - Ramesh (Junnar)", template:"HOLD advice Onion", status:"Read", time:"Today 06:05 AM", lang:"मराठी" },
  { id:"W-4822", channel:"SMS", to:"+91 9xxxx x342 - Sunita More", template:"HOLD advice Tomato", status:"Delivered", time:"Today 06:05 AM", lang:"हिंदी" },
  { id:"W-4820", channel:"WhatsApp", to:"FPO Solapur (23 farmers)", template:"Pool: Tur 40MT matched ₹10200", status:"Replied", time:"Yesterday 07:12 PM", lang:"मराठी" },
  { id:"W-4819", channel:"IVR", to:"+91 9xxxx x887 - Ramesh", template:"Voice: Sell window closing", status:"Delivered", time:"20 Aug 06:10 AM", lang:"मराठी" },
];

export const channelStats = { whatsappPenetration:"94% of farmers in pilot check WhatsApp daily vs 18% open app", cost:"WhatsApp ₹0.35/msg vs App push ₹0", fallback:"SMS if no WhatsApp, IVR call for non-smartphones" };
